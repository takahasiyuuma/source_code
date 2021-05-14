using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class result : MonoBehaviour
{
    [SerializeField] private GameObject black_sphere = null;
    [SerializeField] private GameObject result_texts = null;
    [SerializeField] private GameObject wind_efe = null;
    [SerializeField] private TextMesh S_A_B_C_D_text = null;
    [SerializeField] private TextMesh S_A_B_C_D_text2 = null;
    private int result_state;
    private int buttton_state;
    private float time;

    // Start is called before the first frame update
    void Start()
    {
        result_state = 0;
        buttton_state = 0;
        time = 0.0f;
    }

    // Update is called once per frame
    void Update()
    {
        if(result_state == 1)
        {
            player_move.move_state = 1;
            black_sphere.GetComponent<black_sphere>().alfa_state = 0;

            time += Time.deltaTime;
            if (time >= 5.0f)
            {
                result_state = 2;
            }
        }
        else if(result_state == 2)
        {
            wind_efe.SetActive(false);
            black_sphere.SetActive(true);

            if (target_of_defense.hp >= 100)
            {
                S_A_B_C_D_text.text = $"S";
                S_A_B_C_D_text2.text = $"S";
            }
            else if (target_of_defense.hp >= 70)
            {
                S_A_B_C_D_text.text = $"A";
                S_A_B_C_D_text2.text = $"A";
            }
            else if (target_of_defense.hp >= 50)
            {
                S_A_B_C_D_text.text = $"B";
                S_A_B_C_D_text2.text = $"B";
            }
            else if (target_of_defense.hp >= 20)
            {
                S_A_B_C_D_text.text = $"C";
                S_A_B_C_D_text2.text = $"C";
            }
            else if (target_of_defense.hp >= 0)
            {
                S_A_B_C_D_text.text = $"D";
                S_A_B_C_D_text2.text = $"D";
            }

            result_texts.SetActive(true);

            if (buttton_state == 0)
            {
                Debug.Log("押した");
                if (OVRInput.GetDown(OVRInput.RawButton.RIndexTrigger))
                {
                    Debug.Log("押した");
                    time = 0.0f;
                    buttton_state = 1;
                }
            }
            else if (buttton_state == 1)
            {
                black_sphere.GetComponent<black_sphere>().alfa_state = 3;
                time += Time.deltaTime;
                if (time >= 5.0f)
                {
                    Debug.Log("移行");
                    SceneManager.LoadScene("MainScene");
                }
            }
        }
    }

    private void OnTriggerEnter(Collider collider)
    {
        if (collider.gameObject.tag == "Player")
        {
            result_state = 1;
        }
    }
}
