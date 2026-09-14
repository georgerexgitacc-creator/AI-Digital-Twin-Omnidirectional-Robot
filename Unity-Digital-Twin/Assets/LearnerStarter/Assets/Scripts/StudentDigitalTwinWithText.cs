using UnityEngine;
using TMPro;
using PrayaLabs.OmniRobot;

public class StudentDigitalTwinWithText : MonoBehaviour
{
    [Header("ROBOT")]
    public OmniRobot robot;

    [Header("PRAYA LABS API")]
    public string apiKey;

    [Header("TEXT MESH PRO STATUS")]
    public TMP_Text directionText;
    public TMP_Text frontWheelText;
    public TMP_Text leftWheelText;
    public TMP_Text rightWheelText;

    private void Start()
    {
        robot.SetApiKey(apiKey);
        robot.StartApiReader();
    }

    private void Update()
    {
        if (robot.GetBool("north") == true)
        {
            robot.North();
        }
        else if (robot.GetBool("south") == true)
        {
            robot.South();
        }
        else if (robot.GetBool("northwest") == true)
        {
            robot.NorthWest();
        }
        else if (robot.GetBool("southeast") == true)
        {
            robot.SouthEast();
        }
        else if (robot.GetBool("cw") == true)
        {
            robot.Clockwise();
        }
        else if (robot.GetBool("ccw") == true)
        {
            robot.CounterClockwise();
        }
        else
        {
            robot.Stop();
        }

        UpdateStatus();
    }

    private void UpdateStatus()
    {
        OmniDirection direction = robot.CurrentDirection;

        float front = 0f;
        float left = 0f;
        float right = 0f;

        if (direction == OmniDirection.North)
        {
            if (directionText != null)
                directionText.text = "Direction : NORTH";

            front = 0f;
            left = -1f;
            right = 1f;
        }
        else if (direction == OmniDirection.South)
        {
            if (directionText != null)
                directionText.text = "Direction : SOUTH";

            front = 0f;
            left = 1f;
            right = -1f;
        }
        else if (direction == OmniDirection.NorthWest)
        {
            if (directionText != null)
                directionText.text = "Direction : NORTH WEST";

            front = -1f;
            left = -1f;
            right = 0.5f;
        }
        else if (direction == OmniDirection.SouthEast)
        {
            if (directionText != null)
                directionText.text = "Direction : SOUTH EAST";

            front = 1f;
            left = 1f;
            right = -0.5f;
        }
        else if (direction == OmniDirection.Clockwise)
        {
            if (directionText != null)
                directionText.text = "Direction : CLOCKWISE";

            front = 1f;
            left = 1f;
            right = 1f;
        }
        else if (direction == OmniDirection.CounterClockwise)
        {
            if (directionText != null)
                directionText.text = "Direction : COUNTER CLOCKWISE";

            front = -1f;
            left = -1f;
            right = -1f;
        }
        else
        {
            if (directionText != null)
                directionText.text = "Direction : STOP";

            front = 0f;
            left = 0f;
            right = 0f;
        }

        if (frontWheelText != null)
        {
            if (front > 0f)
                frontWheelText.text = "Front Wheel : FORWARD";
            else if (front < 0f)
                frontWheelText.text = "Front Wheel : BACKWARD";
            else
                frontWheelText.text = "Front Wheel : STOPPED";
        }

        if (leftWheelText != null)
        {
            if (left > 0f)
                leftWheelText.text = "Left Wheel : FORWARD";
            else if (left < 0f)
                leftWheelText.text = "Left Wheel : BACKWARD";
            else
                leftWheelText.text = "Left Wheel : STOPPED";
        }

        if (rightWheelText != null)
        {
            if (right > 0f)
                rightWheelText.text = "Right Wheel : FORWARD";
            else if (right < 0f)
                rightWheelText.text = "Right Wheel : BACKWARD";
            else
                rightWheelText.text = "Right Wheel : STOPPED";
        }
    }

    private void OnDisable()
    {
        if (robot != null)
            robot.StopApiReader();
    }
}
