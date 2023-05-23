using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;
using System;

public class TranslationControl_Opponent : MonoBehaviour
{
    private float desired_X;
    private float desired_Y;
    private Vector3 actual_position;
    private Vector3 starting_position;
    private int delta_X;
    private int delta_Y;
    private bool delta_executed = false;

    // Update is called once per frame
    void Update()
    {
        if (GameObject.FindWithTag("hand_player").GetComponent<Collision>().game_running)
        {
            if (delta_executed == false)
            {
                delta_X = GameObject.FindWithTag("hand_player").GetComponent<Communication>().Encoder_X;
                delta_Y = GameObject.FindWithTag("hand_player").GetComponent<Communication>().Encoder_Y;
                starting_position = this.transform.position;
                delta_executed = true;
            }

            desired_X = starting_position.x + (GameObject.FindWithTag("hand_player").GetComponent<Communication>().Encoder_X - delta_X) * 0.000013f;
            desired_Y = starting_position.z + (GameObject.FindWithTag("hand_player").GetComponent<Communication>().Encoder_Y - delta_Y) * 0.00001f;

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
}