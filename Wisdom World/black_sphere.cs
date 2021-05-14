using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class black_sphere : MonoBehaviour
{
    public int   alfa_state;
    public float speed;            //透明化の速さ
    float        alfa;             //A値を操作するための変数
    float        red, green, blue; //RGBを操作するための変数
    float        time;

    // Start is called before the first frame update
    void Start()
    {
        //元の色を変数に入れる
        red        = GetComponent<MeshRenderer>().material.color.r;
        green      = GetComponent<MeshRenderer>().material.color.g;
        blue       = GetComponent<MeshRenderer>().material.color.b;
        alfa_state = 4;
    }

    // Update is called once per frame
    void Update()
    {
        //変更した色、透明度を反映
        GetComponent<MeshRenderer>().material.color = new Color(red, green, blue, alfa);
        
        //透明度の変更
        if(alfa_state == 0)
        {
            alfa += speed * Time.deltaTime;
            if (alfa >= 1.0f)
            {
                alfa       = 1.0f;
                alfa_state = 1;
            }
        }
        else if(alfa_state == 1)
        {
            time += Time.deltaTime;
            if(time >= 1.5f)
            {
                alfa_state = 2;
            }
        }
        else if (alfa_state == 2)
        {
            alfa -= speed * Time.deltaTime;
            if (alfa <= 0.0f)
            {
                alfa = 0.0f;
            }
        }
        else if(alfa_state == 3)
        {
            alfa += speed * Time.deltaTime;
            if(alfa >= 1.0f)
            {
                alfa = 0.0f;
            }
        }
        else if(alfa_state == 4)
        {
            alfa       = 1.0f;
            alfa_state = 5;
        }
        else if (alfa_state == 5)
        {
            alfa -= speed * Time.deltaTime;
            if (alfa <= 0.0f)
            {
                alfa = 0.0f;
            }
        }

    }
}