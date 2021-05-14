using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Cinemachine;


public class Path_target_move : MonoBehaviour
{
    [SerializeField] private CinemachineDollyCart ob;
    private CinemachineDollyCart cart_;
    void Start()
    {
        cart_ = ob.GetComponent<CinemachineDollyCart>();
    }

    // Update is called once per frame
    void Update()
    {
        cart_.m_Speed = player_move.speed_z;
    }
}