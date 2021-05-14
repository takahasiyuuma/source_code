using UnityEngine;
using UnityEngine.Events;
using UnityEngine.Assertions;
using System.Collections.Generic;
using System.Linq;
using System;

namespace VrGrabber
{

[RequireComponent(typeof(Rigidbody))]
public class VrgGrabber : MonoBehaviour
{
    const float grabBeginThreshold = 0.55f;
    const float grabEndThreshold = 0.35f;
    const float minGrabSmoothDist = 0.5f;
    const float maxGrabSmoothDist = 2f;
    const float minGrabSmoothFilter = 0.15f;
    public ControllerSide side = ControllerSide.Left;

    //
    //※このスクリプト(VrgGrabber)はOculus IntegarionにあるVrgGrabberスクリプトの一部改造したスクリプトです。
    //

    //新たに追加した変数↓
    int          star2_state     = 0;
    int          obj_scale_state = 0;
    float        set_scale       = 1.0f;
    float        set_scale_time  = 0.0f;
    float        effect_time     = 0.0f;
    float        effect2_time    = 0.0f;
    Vector3      start_scale     = new Vector3(1.0f, 1.0f, 1.0f);
    public float scale_speed;
    public float effect_instantiate_time;  //star系は6.5f Erekiball,Sparkは2.5f
    public float effect2_instantiate_time; //star系は6.5f Erekiball,Sparkは2.5f

    [SerializeField] private GameObject effect;
    [SerializeField] private GameObject effect2;
    private List<ParticleSystem>        _particleSystems;
    private List<ParticleSystem>        _particleSystems2;
    public GameObject                   effectPrefab;
    public GameObject                   effectPrefab2;
    //ここまで

    public bool isLeft
    {
        get { return side == ControllerSide.Left; }
    }

    public bool isRight
    {
        get { return side == ControllerSide.Right; }
    }

    [SerializeField]
    Transform grip = null;

    [SerializeField]
    VrgTargetLine line;

    [SerializeField]
    float maxGrabDistance = 10f;

    [SerializeField]
    float stickMoveSpeed = 0.1f;

    [SerializeField]
    LayerMask layerMask = ~0;

    public class TargetClickEvent : UnityEvent<VrgGrabber, RaycastHit> {}
    public TargetClickEvent onTargetClicked = new TargetClickEvent();

    internal class AverageVelocity
    {
        private const int n = 3;
        private Vector3[] velocities_ = new Vector3[n];
        private int index_ = 0;

        public Vector3 average
        {
            get
            {
                var a = Vector3.zero;
                for (int i = 0; i < n; ++i)
                {
                    a += velocities_[i];
                }
                return a / n;
            }
        }

        public void Add(Vector3 velocity)
        {
            velocities_[index_] = velocity;
            index_ = (index_ + 1) % n;
        }
    }

    internal class GrabInfo
    {
        public int id = -1;
        public VrgGrabber grabber = null;
        public VrgGrabbable grabbable = null;
        public Matrix4x4 initGripToGrabbableMat;
        public Matrix4x4 initGrabbableToGrabMat;
        public float distance = 0f;
        public AverageVelocity velocity = new AverageVelocity();
        public bool isKinematic = false;
        public float smoothFilter = 0f;
        public float stickMove = 0f;

        public Matrix4x4 grabMat
        {
            get
            {
                var transMat = Matrix4x4.Translate(new Vector3(0, 0, distance));
                return grabber.gripTransform.localToWorldMatrix * transMat;
            }
        }

        public Matrix4x4 gripToGrabbableMat
        {
            get
            {
                return grabMat * initGripToGrabbableMat;
            }
        }
    }
    GrabInfo grabInfo_ = new GrabInfo();

    internal class DualGrabInfo
    {
        public Vector3 primaryToSecondary;
        public Vector3 pos;
        public Vector3 center;
        public Vector3 scale;
        public Quaternion rot;
    }
    DualGrabInfo dualGrabInfo_ = new DualGrabInfo();

    internal class CandidateInfo
    {
        public VrgGrabbable grabbable;
        public Collider collider;
        public int refCount = 0;
    }
    Dictionary<Collider, CandidateInfo> directGrabCandidates_ = new Dictionary<Collider, CandidateInfo>();

    RaycastHit targetHit_;
    float holdInput_ = 0f;
    bool isHoldStart_ = false;
    bool isHoleEnd_ = false;
    Vector3 preRayDirection_;

    public Transform gripTransform
    {
        get { return grip ? grip : transform; }
    }

    public Vector3 gripDir
    {
        get { return gripTransform.forward; }
    }

    public Vector3 targetPos
    {
        get 
        { 
            if (isGrabbing)
            {
                var grabMat = grabInfo_.grabbable.transform.localToWorldMatrix;
                return (grabMat * grabInfo_.initGrabbableToGrabMat).GetPosition();
            }
            else if (targetHit_.transform)
            {
                return targetHit_.point;
            }
            else if (directGrabCandidates_.Count > 0)
            {
                return gripTransform.position;
            }
            else 
            {
                return gripTransform.position + preRayDirection_ * maxGrabDistance;
            }
        }
    }

    public bool isGrabbing
    {
        get { return grabInfo_.grabbable != null; }
    }

    VrgGrabber opposite
    {
        get
        {
            if (!isGrabbing)
            {
                return null;
            }
            return grabInfo_.grabbable.grabbers.Find(grabber => grabber != this);
        }
    }

    public bool isPrimary
    {
        get
        {
            if (!isGrabbing) return false;

            if (!grabInfo_.grabbable.isMultiGrabbed) return true;

            return grabInfo_.id < opposite.grabInfo_.id;
        }
    }

    void Update()
    {
        UpdateInput();
        UpdateGrab();
    }

    void LateUpdate()
    {
        UpdateTransform();

        if (!isGrabbing)
        {
            UpdateTouch();
        }
    }

    void FixedUpdate()
    {
            if (isGrabbing)
            {
                FixedUpdateGrabbingObject();

                //新たに追加したソースコード

                var grabbable = grabInfo_.grabbable;

                //掴んでいるオブジェクトにエフェクトを付与
                effect_time         += Time.deltaTime;
                effect2_time        += Time.deltaTime;
                GameObject grap_rock = grabbable.gameObject;

                //エフェクトの生成
                if (star2_state == 0)
                {
                    //新しく掴んだ時にエフェクトを一回だけ生成
                    effect      = Instantiate(effectPrefab,  grabbable.position, grabbable.rotation, grap_rock.transform);
                    effect2     = Instantiate(effectPrefab2, grabbable.position, grabbable.rotation, grap_rock.transform);
                    star2_state = 1;

                    //掴んでいるときのエフェクトの再生速度を通常にする
                    _particleSystems = effect.gameObject.GetComponentsInChildren<ParticleSystem>().ToList();
                    foreach (var particle in _particleSystems)
                    {
                        ChangeSpeed(particle, 1.0f);
                    }

                    _particleSystems2 = effect2.gameObject.GetComponentsInChildren<ParticleSystem>().ToList();
                    foreach (var particle in _particleSystems2)
                    {
                        ChangeSpeed(particle, 1.0f);
                    }
                }
                else
                {

                    if (effect_time >= effect_instantiate_time)
                    {
                        //エフェクトを↑秒間隔で生成
                        effect      = Instantiate(effectPrefab, grabbable.position, grabbable.rotation, grap_rock.transform);
                        effect_time = 0.0f;
                    }

                    if(effect2_time >= effect2_instantiate_time)
                    {
                        effect2      = Instantiate(effectPrefab2, grabbable.position, grabbable.rotation, grap_rock.transform);
                        effect2_time = 0.0f;
                    }

                    //掴んでいるときのエフェクトの再生速度を通常にする
                    _particleSystems = effect.gameObject.GetComponentsInChildren<ParticleSystem>().ToList();
                    foreach (var particle in _particleSystems)
                    {
                        ChangeSpeed(particle, 1.0f);
                    }

                    _particleSystems2 = effect2.gameObject.GetComponentsInChildren<ParticleSystem>().ToList();
                    foreach (var particle in _particleSystems2)
                    {
                        ChangeSpeed(particle, 1.0f);
                    }
                }
            }
            else
            {
                if (star2_state == 1)
                {
                    //掴んでいないときのエフェクトの再生速度を早くする
                    _particleSystems = effect.gameObject.GetComponentsInChildren<ParticleSystem>().ToList();
                    foreach (var particle in _particleSystems)
                    {
                        ChangeSpeed(particle, 3.0f);
                    }

                    _particleSystems2 = effect2.gameObject.GetComponentsInChildren<ParticleSystem>().ToList();
                    foreach (var particle in _particleSystems2)
                    {
                        ChangeSpeed(particle, 3.0f);
                    }
                    star2_state = 0;
                }

                //掴んでいないときに変数を初期化
                effect_time     = 0.0f;
                obj_scale_state = 0;
            }
        }

    //エフェクトの再生速度の設定
    private void ChangeSpeed(ParticleSystem particle, float speed)
    {
        var main             = particle.main;
        main.simulationSpeed = speed;
    }

    //ここまで

    void OnTriggerEnter(Collider collider)
    {
        var grabbable =
            collider.GetComponent<VrgGrabbable>() ??
            collider.GetComponentInParent<VrgGrabbable>();
        if (!grabbable) return;

        CandidateInfo info;
        if (!directGrabCandidates_.TryGetValue(collider, out info))
        {
            info = new CandidateInfo();
            info.collider = collider;
            info.grabbable = grabbable;
            directGrabCandidates_.Add(collider, info);
        }
        info.refCount++;
    }

    void OnTriggerExit(Collider collider)
    {
        CandidateInfo info = null;
        if (!directGrabCandidates_.TryGetValue(collider, out info)) return;

        info.refCount--;
        if (info.refCount <= 0)
        {
            directGrabCandidates_.Remove(collider);
        }
    }

    void UpdateTransform()
    {
        transform.localPosition = Device.instance.GetLocalPosition(side);
        transform.localRotation = Device.instance.GetLocalRotation(side);
    }

    void UpdateInput()
    {
        var preHoldInput = holdInput_;
        holdInput_ = Device.instance.GetHold(side);
        isHoldStart_ = (holdInput_ >= grabBeginThreshold) && (preHoldInput < grabBeginThreshold);
        isHoleEnd_ = (holdInput_ <= grabEndThreshold) && (preHoldInput > grabEndThreshold);
    }

    void UpdateGrab()
    {
        if (isHoldStart_)
        {
            DirectGrab();
            RemoteGrab();
        }
        else if (isHoleEnd_)
        {
            Release();
        }
    }

    void UpdateTouch()
    {
        var forward = gripTransform.forward;
        
        var ray = new Ray();
        ray.origin = gripTransform.position;
        ray.direction = Vector3.Lerp(preRayDirection_, forward, 0.25f);

        targetHit_ = new RaycastHit();
        bool hit = Physics.Raycast(ray, out targetHit_, maxGrabDistance, layerMask);
        preRayDirection_ = hit ? ray.direction : forward;
    }

    void Grab(VrgGrabbable grabbable, float distance)
    {
        grabInfo_.grabber = this;
        grabInfo_.grabbable = grabbable;
        grabInfo_.distance = distance;
        var grabMat = grabInfo_.grabMat;
        grabInfo_.initGripToGrabbableMat = grabMat.inverse * grabbable.transform.localToWorldMatrix;
        grabInfo_.initGrabbableToGrabMat = grabbable.transform.worldToLocalMatrix * grabMat;
        grabInfo_.isKinematic = grabbable.rigidbody.isKinematic;

        if (!grabbable.avoidIntersection)
        {
            grabbable.rigidbody.isKinematic = true;
        }

        if (grabbable.isGrabbed)
        {
            SecondGrab(grabbable);
        }

        grabInfo_.id = grabbable.OnGrabbed(this);
    }

    void DirectGrab()
    {
        if (isGrabbing || directGrabCandidates_.Count == 0) return;

        VrgGrabbable grabbable = null;
        float minDist = float.MaxValue;

        var gripPos = gripTransform.position;
        foreach (var kv in directGrabCandidates_)
        {
            var candidate = kv.Value;
            var pos = candidate.collider.ClosestPoint(gripPos);
            var dist = Vector3.Distance(gripPos, pos);

            if (dist < minDist)
            {
                grabbable = candidate.grabbable;
                minDist = dist;
            }
        }

        if (grabbable)
        {
            Grab(grabbable, 0f);
        }
    }

    void RemoteGrab()
    {
        if (isGrabbing) return;

        var ray = new Ray();
        ray.origin = gripTransform.position;
        ray.direction = gripTransform.forward;
        RaycastHit hit;

        if (!Physics.Raycast(ray, out hit, maxGrabDistance, layerMask))
        {
            return;
        }

        var grabbable =
            hit.collider.GetComponent<VrgGrabbable>() ??
            hit.collider.GetComponentInParent<VrgGrabbable>();

        if (grabbable)
        {
            Grab(grabbable, hit.distance);
        }
    }

    void SecondGrab(VrgGrabbable grabbable)
    {
        var primary = opposite;
        var secondary = this;

        var primaryMat = primary.grabInfo_.gripToGrabbableMat;
        var secondaryMat = secondary.grabInfo_.gripToGrabbableMat;
        var primaryPos = primaryMat.GetPosition();
        var secondaryPos = secondaryMat.GetPosition();
        var primaryGripPos = primary.gripTransform.position;
        var secondaryGripPos = secondary.gripTransform.position;

        primary.dualGrabInfo_.primaryToSecondary = primaryGripPos - secondaryGripPos;
        primary.dualGrabInfo_.pos = grabbable.transform.position;
        primary.dualGrabInfo_.center = (primaryPos + secondaryPos) / 2;
        primary.dualGrabInfo_.rot = grabbable.transform.rotation;
        primary.dualGrabInfo_.scale = grabbable.transform.localScale;

        grabInfo_.isKinematic = primary.grabInfo_.isKinematic;
    }

    void Release()
    {
        if (!isGrabbing) return;

        var grabbable = grabInfo_.grabbable;

        Assert.IsTrue(grabbable.isGrabbed);

        grabbable.velocity = grabInfo_.velocity.average;
        grabbable.OnReleased(this);

        if (grabbable.isGrabbed)
        {
            // opposite.ReGrab();
        }
        else
        {
            grabbable.rigidbody.isKinematic = grabInfo_.isKinematic;
        }

        grabInfo_ = new GrabInfo();
    }

    void ReGrab()
    {
        var grabbable = grabInfo_.grabbable;
        if (!grabbable) return;

        var grabMat = grabInfo_.grabMat;
        grabInfo_.initGripToGrabbableMat = grabMat.inverse * grabbable.transform.localToWorldMatrix;
    }

    void FixedUpdateGrabbingObject()
    {
        if (Device.instance.GetClick(side))
        {
            grabInfo_.grabbable.OnGrabClicked(this);
        }

        if (grabInfo_.grabbable.isMultiGrabbed)
        {
            //今回の作品では使わないのでコメントアウト
            //FixedUpdateGrabbingObjectByDualHand();
        }
        else
        {
            FixedUpdateGrabbingObjectBySingleHand();
        }
    }

    void FixedUpdateGrabbingObjectBySingleHand()
    {
        var stickY = Device.instance.GetCoord(side).y;
        var stickMove = stickY * stickMoveSpeed;
        var stickMoveFilter = stickY > Mathf.Epsilon ? 0.1f : 0.3f;
        grabInfo_.stickMove += (stickMove - grabInfo_.stickMove) * stickMoveFilter;

        var dist = Mathf.Clamp(grabInfo_.distance + grabInfo_.stickMove, 0f, maxGrabDistance);
        var actualDist = (targetPos - gripTransform.position).magnitude;
        var deltaDist = dist - actualDist;
        var threshDist = Mathf.Max(dist * 0.1f, 0.1f);
        if (Mathf.Abs(deltaDist) > threshDist)
        {
            dist = Mathf.Lerp(grabInfo_.distance, actualDist, 0.05f);
        }
        grabInfo_.distance = dist;

        //新たに追加したソースコード

        var     mat       = grabInfo_.gripToGrabbableMat;
        var     pos       = mat.GetPosition();
        var     rot       = mat.GetRotation();
        Vector3 obj_scale = mat.GetScale();

        //新しく掴んだオブジェクトの情報を最初に一回だけ取得
        if (obj_scale_state == 0)
        {
            set_scale       = obj_scale.x;
            start_scale     = mat.GetScale();
            obj_scale_state = 1;
        }

        //スティックでのスケールの操作
        set_scale_time += Time.deltaTime;
        if (OVRInput.Get(OVRInput.RawButton.RThumbstickUp))
        {
            Debug.Log("右アナログスティックを上に倒した");

            //徐々に拡大
            if(set_scale_time >= 0.1f)
            {
                set_scale += scale_speed;
            }
        }
        else if (OVRInput.Get(OVRInput.RawButton.RThumbstickDown))
        {
            Debug.Log("右アナログスティックを下に倒した");

            //徐々に縮小
            if (set_scale_time >= 0.1f)
            {
                set_scale -= scale_speed;
            }
        }

       //スケールに使用しているタイムの初期化
       if (set_scale_time >= 0.1f)
       {
            set_scale_time = 0.0f;
       }

       //スケールの拡大、縮小の限界を設定
       if (set_scale >= start_scale.x * 2.0f)
       {
            set_scale = start_scale.x * 2.0f;
       }
       else if(set_scale <= start_scale.x * 0.3f)
       {
            set_scale = start_scale.x * 0.3f;
       }

       //スケールの設定、反映
       var scale = new Vector3(set_scale,set_scale,set_scale);
       FixedUpdateGrabbingObjectTransform(pos, rot, scale);
    }

    //ここまで

    //今回の作品では使わないのでコメントアウト↓
    //void FixedUpdateGrabbingObjectByDualHand()
    //{
    //    if (!isPrimary) return;

    //    var secondary = opposite;
    //    Assert.IsNotNull(secondary);

    //    var primaryGripPos = gripTransform.position;
    //    var primaryGripRot = gripTransform.rotation;
    //    var secondaryGripPos = secondary.gripTransform.position;
    //    var secondaryGripRot = secondary.gripTransform.rotation;

    //    var primaryMat = grabInfo_.gripToGrabbableMat;
    //    var secondaryMat = secondary.grabInfo_.gripToGrabbableMat;
    //    var primaryPos = primaryMat.GetPosition();
    //    var secondaryPos = secondaryMat.GetPosition();

    //    var center = (primaryPos + secondaryPos) / 2;
    //    var dCenter = center - dualGrabInfo_.center;
    //    var pos = dualGrabInfo_.pos + dCenter;

    //    var primaryToSecondary = primaryGripPos - secondaryGripPos;
    //    var currentDir = primaryToSecondary.normalized;
    //    var initDir = dualGrabInfo_.primaryToSecondary.normalized;
    //    var dRot = Quaternion.FromToRotation(initDir, currentDir);
    //    var rot = dRot * dualGrabInfo_.rot;
    //    var scale = dualGrabInfo_.scale;

    //        //if (grabInfo_.grabbable.isScalable)
    //        //{
    //        //    var currentDistance = primaryToSecondary.magnitude;
    //        //    var initDistance = dualGrabInfo_.primaryToSecondary.magnitude;
    //        //    scale *= (currentDistance / initDistance) * 3;
    //        //    ↑スケールを変える処理の場所
    //        //}

    //    grabInfo_.smoothFilter = 0f;
    //    FixedUpdateGrabbingObjectTransform(pos, rot, scale);
    //}

    void FixedUpdateGrabbingObjectTransform(Vector3 pos, Quaternion rot, Vector3 scale)
    {
        var grabbable = grabInfo_.grabbable;

        var a = (Mathf.Clamp(grabInfo_.distance, minGrabSmoothDist, maxGrabSmoothDist) - minGrabSmoothDist) / (maxGrabSmoothDist - minGrabSmoothDist);
        var targetFilter = 1f - (1f - minGrabSmoothFilter) * a;
        var filter = grabInfo_.smoothFilter + (targetFilter - grabInfo_.smoothFilter) * 0.1f;
        grabInfo_.smoothFilter = filter;

        pos = Vector3.Lerp(grabbable.position, pos, filter);
        scale = Vector3.Lerp(grabbable.transform.localScale, scale, filter);

        var v = (pos - grabbable.position) / Time.fixedDeltaTime;
        grabInfo_.velocity.Add(v);

        grabbable.scale = scale;
        grabbable.position = pos;
        grabbable.rotation = rot;
    }
}

}
