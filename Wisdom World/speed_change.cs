using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Cinemachine;

public class speed_change : MonoBehaviour
{
    [SerializeField] private CinemachineDollyCart dollycart;
    float time;

    // Start is called before the first frame update
    void Start()
    {
        time = 0.0f;
    }

    // Update is called once per frame
    void Update()
    {
        time += Time.deltaTime;
        if (dollycart.m_Position >= 65000.0f)
        {
            if (player_move.speed_z <= 495)
            {
                if (time >= 0.1f)
                {
                    player_move.speed_z += 5.0f;
                    time = 0.0f;
                }
            }
        }
        else if (dollycart.m_Position >= 40000.0f)
        {
            if (player_move.speed_z >= 305)
            {
                if (time >= 0.1f)
                {
                    player_move.speed_z -= 5.0f;
                    time = 0.0f;
                }
            }
        }
    }
}
