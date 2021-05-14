using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class broom_rotation : MonoBehaviour
{
    [SerializeField] private Transform handTrans_L = null;

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        //コントローラー、ヘットセットのtransform.rotationを取得してほうきの向きを
        //コントローラー、ヘットセットと同じ方向を向くようにする

        //コントローラーの時
        //transform.rotation = handTrans_L.rotation * Quaternion.Euler(35, -180, 0);

        //ヘットセットの時
        transform.rotation = handTrans_L.rotation * Quaternion.Euler(0, -180, 0);
    }
}