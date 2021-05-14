using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class star2 : MonoBehaviour
{
    ParticleSystem particle;
    void Start()
    {
        particle = this.GetComponent<ParticleSystem>();
    }

    void Update()
    {
        //エフェクトの再生
        if (particle.isStopped)       //パーティクルが終了したか判別
        {
            Destroy(this.gameObject); //パーティクル用ゲームオブジェクトを削除
        }
    }
}
