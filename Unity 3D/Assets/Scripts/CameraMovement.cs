using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraMovement : MonoBehaviour
{
    public Vector3 target_position;
    public Quaternion target_rotation;
    public float smooth = 3;
    public Vector3 actual_position;
    public Quaternion actual_rotation;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    // Camera zooms into game arena when game starts
    void Update()
    {
        if (GameObject.FindWithTag("hand_player").GetComponent<Collision>().game_running)
        {
            target_rotation = Quaternion.Euler(35, 0, 0);
            target_position = new Vector3(0, 0.3f, -0.4f);
            transform.position = Vector3.Slerp (transform.position, target_position, smooth * Time.deltaTime);
            transform.rotation = Quaternion.Slerp (transform.rotation, target_rotation, smooth * Time.deltaTime);
        }
    }
}
