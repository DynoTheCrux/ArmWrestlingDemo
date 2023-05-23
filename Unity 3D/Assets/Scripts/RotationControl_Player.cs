using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RotationControl_Player : MonoBehaviour
{
    private float desired_W;

    // Update is called once per frame
    void Update()
    {
        desired_W = 140 + GameObject.FindWithTag("hand_player").GetComponent<Communication>().Encoder_W * 0.1f;

        //Rotation of elbow
        this.transform.rotation = Quaternion.Euler(0, 0, desired_W);
    }
}
