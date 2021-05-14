using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class fire_ball : MonoBehaviour
{
    public GameObject        particleObject;
    [SerializeField] private Transform target;
    public float             speed;

    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        transform.rotation  = Quaternion.Slerp(transform.rotation, Quaternion.LookRotation(target.position - transform.position), 0.3f);
        transform.position += transform.forward * speed;
    }

    private void OnTriggerEnter(Collider collider)
    {
        //Rock(grab_defense_rock)の衝突判定
        if (collider.gameObject.tag == "Rock")
        {
            Debug.Log  ("小障害物に当たった(FireBall)");
            Instantiate(particleObject, this.transform.position, Quaternion.identity); //パーティクル用ゲームオブジェクト生成
            Destroy    (this.gameObject);                                              //衝突したゲームオブジェクトを削除
        }

        //ドラゴンの衝突判定(デバック)
        if (collider.gameObject.tag == "Dragon")
        {
            Debug.Log("ドラゴンに当たった(FireBall)");
        }
    }
}