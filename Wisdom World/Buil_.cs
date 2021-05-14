using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Buil_ : MonoBehaviour
{
    [SerializeField] private GameObject[] roofs;
    // Start is called before the first frame update
    void Start()
    {
        //まちのモデルの屋根のオブジェクトだけを取得
        roofs = GameObject.FindGameObjectsWithTag("town");

        //取得した屋根のオブジェクトの色をランダムでつける
        for (int i = 0; i < roofs.Length; i++)
        {
            roofs[i].GetComponent<Renderer>().material.color = new Color(Random.value, Random.value, Random.value, 1);
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
