using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RotationControl_Opponent : MonoBehaviour
{
    private float angle;

    // Update is called once per frame
    void Update()
    {
        //Rotation of elbow (allowed only if game is running)
        if (GameObject.FindWithTag("hand_player").GetComponent<Collision>().game_running)
        {
            angle = 140 + GameObject.FindWithTag("hand_player").GetComponent<Communication>().Encoder_W * 0.1f;
            this.transform.rotation = Quaternion.Euler(0, 180, -angle);
        }
    }
}
