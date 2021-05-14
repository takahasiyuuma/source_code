using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class game_over_text : MonoBehaviour
{
    public float speed;     //透明化の速さ
    float alfa;             //A値を操作するための変数
    float red, green, blue; //RGBを操作するための変数

    // Start is called before the first frame update
    void Start()
    {
        //元の色を変数に入れる
        red   = GetComponent<TextMesh>().color.r;
        green = GetComponent<TextMesh>().color.g;
        blue  = GetComponent<TextMesh>().color.b;
    }

    // Update is called once per frame
    void Update()
    {
        //変更した色、透明度を反映
        GetComponent<TextMesh>().color = new Color(red, green, blue, alfa);

        //透明度の変更
        alfa += speed * Time.deltaTime;
        if (alfa >= 1.0f)
        {
            alfa = 1.0f;
        }
    }
}