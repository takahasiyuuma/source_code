﻿using UnityEngine;
using UnityEngine.SceneManagement;
using System.Collections;

public class playermove : MonoBehaviour
{
    [SerializeField] private Transform OVRCameraRig = null;
    [SerializeField] private GameObject red_window = null;

    //佐藤
    [SerializeField] private GameObject player;

    public float inertia_x;
    public float inertia_y;
    public float acceleration_z;
    public float max_speed_z;
    public float min_speed_z;
    public float brake_x;
    public float brake_y;
    public float brake_z;
    public float speed_time;
    public float inertia_speed_max_x;
    public float inertia_speed_min_x;
    public float inertia_speed_max_y;
    public float inertia_speed_min_y;
    private float time;
    static public int move_state;
    private int red_window_time;
    private float speed_x;
    private float speed_y;
    private float inertia_speed_time;
    public static float speed_z;
    private int start_state;

    //佐藤
    private float pos_x;
    private float pos_y;
    private float pos_z;

    private Rigidbody rigidbody;

    // Start is called before the first frame update
    void Start()
    {
        speed_x = 0.0f;
        speed_y = 0.0f;
        speed_z = 500.0f; //旧マップ Town 300.0f; Cliff 150.0f; Tower 450.0f; 新マップ Town 600.0f; Cliff 300.0f; Tower 500.0f;
        time = 0.0f;
        move_state = 0;
        inertia_speed_time = 0.0f;
        start_state = 0;
        rigidbody = GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    void Update()
    {
        OVRInput.Update();

        //佐藤
        pos_x = Mathf.Clamp(player.transform.position.x, -72.0f, 72.0f);
        pos_y = Mathf.Clamp(player.transform.position.y, 0f, 120.0f);
        pos_z = Mathf.Clamp(player.transform.position.z, -2224.0f, 23444.0f);


        if(move_state == 0 || start_state == 1)
        {
            inertia_speed_time += Time.deltaTime;
            //ヘットセットでのX座標移動処理↓(インスペクター上のセンターアイの数値は偽なので注意(マイナスの数値は存在しない)）
            if (OVRCameraRig.localRotation.eulerAngles.z >= 10.0f && OVRCameraRig.localRotation.eulerAngles.z <= 100.0f)
            {
                if (inertia_speed_time >= 0.1f)
                {
                    speed_x -= inertia_x;
                }
            }
            else if (OVRCameraRig.localRotation.eulerAngles.z >= 260.0f && OVRCameraRig.localRotation.eulerAngles.z <= 350.0f)
            {
                if (inertia_speed_time >= 0.1f)
                {
                    speed_x += inertia_x;
                }
            }
            else
            {
                if (speed_x != 0)
                {
                    if (speed_x > 0)
                    {
                        if (inertia_speed_time >= 0.1f)
                        {
                            speed_x -= brake_x;
                        }
                    }
                    else if (speed_x < 0)
                    {
                        if (inertia_speed_time >= 0.1f)
                        {
                            speed_x += brake_x;
                        }
                    }
                }
            }

            if (speed_x >= inertia_speed_max_x)
            {
                speed_x = inertia_speed_max_x;
            }
            else if (speed_x <= inertia_speed_min_x)
            {
                speed_x = inertia_speed_min_x;
            }

            //ヘットセットでのY座標移動処理↓
            if (OVRCameraRig.localRotation.eulerAngles.x >= 10.0f && OVRCameraRig.localRotation.eulerAngles.x <= 100.0f)
            {
                if (inertia_speed_time >= 0.1f)
                {
                    speed_y -= inertia_y;
                }
            }
            else if (OVRCameraRig.localRotation.eulerAngles.x >= 260.0f && OVRCameraRig.localRotation.eulerAngles.x <= 350.0f)
            {
                if (inertia_speed_time >= 0.1f)
                {
                    speed_y += inertia_y;
                }
            }
            else
            {
                if (speed_y != 0)
                {
                    if (speed_y > 0)
                    {
                        if (inertia_speed_time >= 0.1f)
                        {
                            speed_y -= brake_y;
                        }
                    }
                    else if (speed_y < 0)
                    {
                        if (inertia_speed_time >= 0.1f)
                        {
                            speed_y += brake_y;
                        }
                    }
                }
            }

            if (speed_y >= inertia_speed_max_y)
            {
                speed_y = inertia_speed_max_y;
            }
            else if (speed_y <= inertia_speed_min_y)
            {
                speed_y = inertia_speed_min_y;
            }

            if (inertia_speed_time >= 0.1f)
            {
                inertia_speed_time = 0.0f;
            }

            //タイム計測↓
            time += Time.deltaTime;
            if (time >= 1.0f)
            {
                //衝突時のエフェクト表示時間処理↓
                if (red_window.activeInHierarchy)
                {
                    red_window_time += 1;

                    if (red_window_time >= 2)
                    {
                        red_window.SetActive(false);
                    }
                }
                time = 0.0f;
            }
        }
        else
        {
            speed_x = 0.0f;
            speed_y = 0.0f;
            speed_z = 0.0f;
        }

        rigidbody.velocity = new Vector3(transform.right.x * speed_x, transform.up.y * speed_y, 0.0f);
    }
    private void OnTriggerEnter(Collider collider)
    {
        //10%ダメージオブジェクトの判定↓（タグは後付け）
        if (collider.gameObject.tag == "Fire_Ball")
        {
            red_window.SetActive(false);
            time = 0.0f;
            speed_time = 0.0f;
            red_window_time = 0;
            red_window.GetComponent<red_window>().alfa = 0.0f;
            red_window.GetComponent<red_window>().alfa_state = 0;
            red_window.GetComponent<red_window>().time = 0.0f;
            Debug.Log("10%ダメージオブジェクトに当たった");
            red_window.SetActive(true);
        }

        //20%ダメージオブジェクトの判定↓（タグは後付け）
        if (collider.gameObject.tag == "fall_down_tower")
        {
            red_window.SetActive(false);
            time = 0.0f;
            speed_time = 0.0f;
            red_window_time = 0;
            red_window.GetComponent<red_window>().alfa = 0.0f;
            red_window.GetComponent<red_window>().alfa_state = 0;
            red_window.GetComponent<red_window>().time = 0.0f;
            Debug.Log("20%ダメージオブジェクトに当たった");
            red_window.SetActive(true);
        }
    }
}