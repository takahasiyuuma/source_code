using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class target_of_defense : MonoBehaviour
{
    // Start is called before the first frame update

    [SerializeField] private GameObject black_window = null;
    [SerializeField] private GameObject game_over_texts = null;
    [SerializeField] private GameObject wind_efe = null;
    static public int hp;
    private int invincible_state;
    private float time;
    private float speed_time;

    private int alfa_state;
    private float alfa;    //A値を操作するための変数
    public float speed;  //透明化の速さ
    private float red, green, blue;    //RGBを操作するための変数
    SkinnedMeshRenderer meshrender;

    void Start()
    {
        hp = 100;
        invincible_state = 0;
        time = 0.0f;
        speed_time = 0.0f;

        meshrender = GetComponent<SkinnedMeshRenderer>();
        red = GetComponent<SkinnedMeshRenderer>().material.color.r;
        green = GetComponent<SkinnedMeshRenderer>().material.color.g;
        blue = GetComponent<SkinnedMeshRenderer>().material.color.b;
        alfa_state = 0;
        alfa = 1.0f;
    }

    // Update is called once per frame
    void Update()
    {
        meshrender.material.color = new Color(red, green, blue, alfa);

        if (invincible_state == 1)
        {
            if (alfa >= 1.0f)
            {
                alfa_state = 1;
            }
            else if (alfa <= 0.2f)
            {
                alfa_state = 0;
            }

            if (alfa_state == 0)
            {
                alfa += speed * Time.deltaTime;
            }
            else if (alfa_state == 1)
            {
                alfa -= speed * Time.deltaTime;
            }

            time += Time.deltaTime;
            if (time >= 2.0f)
            {
                invincible_state = 0;
            }
        }
        else
        {
            time = 0.0f;

            if(alfa >= 1.0f)
            {
                alfa = 1.0f;
            }
            else if(alfa <= 1.0f)
            {
                alfa += speed * Time.deltaTime;
            }
        }

        if (hp <= 0)
        {
            //ゲームオーバー処理
            playermove.move_state = 1;
            wind_efe.SetActive(false);
            black_window.SetActive(true);
            game_over_texts.SetActive(true);
            speed_time += Time.deltaTime;
            if(speed_time >= 0.1f)
            {
                playermove.speed_z -= 10.0f;
                speed_time = 0.0f;
            }
        }
    }

    private void OnTriggerEnter(Collider collider)
    {
        if (invincible_state == 0)
        {
            //10%ダメージの判定↓(タグは後付け)
            if (collider.gameObject.tag == "Fire_Ball")
            {
                hp -= 10;
                time = 0.0f;
                alfa = 1.0f;
                alfa_state = 0;
                Debug.Log("10%ダメージ");
                invincible_state = 1;
            }

            //20%ダメージの判定↓(タグは後付け)
            if (collider.gameObject.tag == "fall_down_tower")
            {
                hp -= 20;
                time = 0.0f;
                alfa = 1.0f;
                alfa_state = 0;
                Debug.Log("20%ダメージ");
                invincible_state = 1;
            }
        }
    }
}
