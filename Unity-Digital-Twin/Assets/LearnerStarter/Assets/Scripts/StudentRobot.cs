using UnityEngine;
using PrayaLabs.OmniRobot;

public class StudentRobot : MonoBehaviour
{
    public OmniRobot robot;

    private void Update()
    {
        if (Input.GetKey(KeyCode.Q))
            robot.North();

        else if (Input.GetKey(KeyCode.W))
            robot.South();

        else if (Input.GetKey(KeyCode.E))
            robot.NorthWest();

        else if (Input.GetKey(KeyCode.R))
            robot.SouthEast();

        else if (Input.GetKey(KeyCode.T))
            robot.Clockwise();

        else if (Input.GetKey(KeyCode.Y))
            robot.CounterClockwise();

        else
            robot.Stop();
    }
}
