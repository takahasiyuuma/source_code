using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class grab_defense_rock : MonoBehaviour
{
    public GameObject particleObject;

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        //拡大、縮小の限界の設定
        if (gameObject.transform.localScale.x >= 20.0f && gameObject.transform.localScale.y >= 20.0f && gameObject.transform.localScale.z >= 20.0f)
        {
            Vector3 scale                   = new Vector3(20.0f, 20.0f, 20.0f);  //仮の変数宣言＆初期化
            gameObject.transform.localScale = scale;                             //位置座標に変数を代入
        }
    }
    private void OnTriggerEnter(Collider collider)
    {
        //敵の攻撃用オブジェクトとの衝突判定
        if (collider.gameObject.tag == "Fire_Ball")
        {
            Debug.Log  ("火の玉に当たった(DefenseRock)");
            Instantiate(particleObject, this.transform.position, Quaternion.identity); //パーティクル用ゲームオブジェクト生成
            Destroy    (this.gameObject);                                              //衝突したゲームオブジェクトを削除
        }
    }
}
