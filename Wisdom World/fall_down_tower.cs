using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Cinemachine;

public class fall_down_tower : MonoBehaviour
{
    [SerializeField] private CinemachineDollyCart dollycart;
    float        time;
    public float position;
    public float speed;
    public float max_z_rotation;

    // Start is called before the first frame update
    void Start()
    {
        time = 0.0f;
    }

    // Update is called once per frame
    void Update()
    {
        //塔の倒壊
        time                 += Time.deltaTime;
        Transform myTransform = this.transform;
        Vector3   rotation    = myTransform.eulerAngles;
        if (rotation.z >= max_z_rotation)
        {
            rotation.z = max_z_rotation;
        }
        else
        {
            //プレイヤーが一定の距離まで進むと塔の倒壊を開始
            if (dollycart.m_Position >= position)
            {
                //徐々に倒れていく
                if (time >= 0.01f)
                {
                    rotation.z += speed;
                    time        = 0.0f;
                }
            }
        }
        myTransform.eulerAngles = rotation;
    }
}