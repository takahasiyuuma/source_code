using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class red_window : MonoBehaviour
{
    public float speed;            //透明化の速さ
    public float alfa;             //A値を操作するための変数
    public float red, green, blue; //RGBを操作するための変数
    public int   alfa_state;
    public float time;
    // Start is called before the first frame update
    void Start()
    {
        //元の色を変数に入れる
        red        = GetComponent<Image>().color.r;
        green      = GetComponent<Image>().color.g;
        blue       = GetComponent<Image>().color.b;
        time       = 0.0f;
        alfa_state = 0;
    }

    // Update is called once per frame
    void Update()
    {
        //変更した色、透明度を反映
        GetComponent<Image>().color = new Color(red, green, blue, alfa);

        //透明度の変更
        time += Time.deltaTime;
        if(alfa_state == 0)
        {
            if (time >= 0.1f)
            {
                alfa += speed * Time.deltaTime;
            }

            if (alfa >= 0.8f)
            {
                alfa_state = 1;
            }
        }
        else if (alfa_state == 1)
        {
            if (time >= 0.1f)
            {
                alfa -= speed * Time.deltaTime;
            }

            if (alfa <= 0.0f)
            {
                alfa_state = 0;
            }
        }
    }
}