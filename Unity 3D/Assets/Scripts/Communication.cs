using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Communication : MonoBehaviour
{
    public SerialController serialController;
    public int Encoder_X = 0;
    public int Encoder_Y = 0;
    public int Encoder_W = 0;
    public string enc_values = "";

    // Start is called before the first frame update
    void Start()
    {
        serialController = GameObject.Find("SerialController").GetComponent<SerialController>();
    }

    // Update is called once per frame
    void Update()
    {
        //Receive encoder information from Arduino
        enc_values = serialController.ReadSerialMessage();
        string[] enc_list = enc_values.Split(' ');
        Encoder_X = int.Parse(enc_list[0]);
        Encoder_Y = int.Parse(enc_list[1]);
        Encoder_W = int.Parse(enc_list[2]);
    }
}