using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Win : MonoBehaviour
{
    public int score = 0;
    public Text countText;
    public Text winText;
    public static bool game_over = false;


    // Start is called before the first frame update
    void Start()
    {
        winText.text = "";   
    }

    // Update is called once per frame
    // Game instructions shown to player
    void Update()
    {
        if (GameObject.FindWithTag("hand_player").GetComponent<Collision>().game_running == false)
        {
            countText.text = "Move your arm to the opponent to start the game. Win the game by forcing the opponent's arm down 4 times.";
        }
    }

    // Win text shown to the player
    void OnTriggerEnter()
    {
        score++;
        countText.text = "Score: " + score.ToString();
        if (score >=4)
        {
            winText.text = "You won the game! Remove your arm from the device and press R to restart!";
            game_over = true;
        }
        game_over = true;
    }
}