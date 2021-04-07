using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class fire_ball : MonoBehaviour
{
    public GameObject particleObject;
    [SerializeField] private Transform target;
    public float speed;
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        transform.rotation = Quaternion.Slerp(transform.rotation, Quaternion.LookRotation(target.position - transform.position), 0.3f);
        transform.position += transform.forward * speed;
    }

    private void OnTriggerEnter(Collider collider)
    {
        //小障害物
        if (collider.gameObject.tag == "Debug")
        {
            Debug.Log("小障害物に当たった(FireBall)");
            Instantiate(particleObject, this.transform.position, Quaternion.identity); //パーティクル用ゲームオブジェクト生成
            Destroy(this.gameObject); //衝突したゲームオブジェクトを削除
        }

        //ドラゴンに当たった時
        if (collider.gameObject.tag == "Dragon")
        {
            Debug.Log("ドラゴンに当たった(FireBall)");
        }
    }
}