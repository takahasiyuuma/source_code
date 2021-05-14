using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class game_over_press_button : MonoBehaviour
{
    public float speed;            //透明化の速さ
    public float alfa;             //A値を操作するための変数
    public float red, green, blue; //RGBを操作するための変数
    public int   alfa_state;

    // Start is called before the first frame update
    void Start()
    {
        //元の色を変数に入れる
        red        = GetComponent<TextMesh>().color.r;
        green      = GetComponent<TextMesh>().color.g;
        blue       = GetComponent<TextMesh>().color.b;
        alfa_state = 0;
    }

    // Update is called once per frame
    void Update()
    {
        //変更した色、透明度を反映
        GetComponent<TextMesh>().color = new Color(red, green, blue, alfa);

        //透明度の変更
        if(alfa_state == 0)
        {
            if (alfa >= 1.0f)
            {
                alfa_state = 1;
            }
        }
        else
        {
            if (alfa >= 0.6f)
            {
                alfa_state = 2;
            }
            else if (alfa <= 0.2f)
            {
                alfa_state = 1;
            }
        }

        if(alfa_state == 0)
        {
            alfa += speed * Time.deltaTime;
        }
        else if (alfa_state == 1)
        {
            alfa += speed * Time.deltaTime;
        }
        else if (alfa_state == 2)
        {
            alfa -= speed * Time.deltaTime;
        }
    }
}