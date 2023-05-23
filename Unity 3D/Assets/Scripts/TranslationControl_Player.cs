using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;
using System;

public class TranslationControl_Player : MonoBehaviour
{
    private float desired_X;
    private float desired_Y;
    private Vector3 actual_position;

    // Update is called once per frame
    void Update()
    {
        desired_X = -0.2f + GameObject.FindWithTag("hand_player").GetComponent<Communication>().Encoder_X * 0.000013f;
        desired_Y = -0.45f + GameObject.FindWithTag("hand_player").GetComponent<Communication>().Encoder_Y * 0.00001f;

        // Translation in X
        actual_position = this.transform.position;
        while (actual_position.x < desired_X)
        {
            actual_position.x = actual_position.x + 0.001f;
        }
        while (actual_position.x > desired_X)
        {
            actual_position.x = actual_position.x - 0.001f;
        }
        //Translation in Y
        while (actual_position.z < desired_Y)
        {
            actual_position.z = actual_position.z + 0.001f;
        }
        while (actual_position.z > desired_Y)
        {
            actual_position.z = actual_position.z - 0.001f;
        }
        this.transform.position = actual_position;
    }
}