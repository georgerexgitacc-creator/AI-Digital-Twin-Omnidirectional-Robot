using UnityEngine;
using PrayaLabs.OmniRobot;

public class StudentDigitalTwin : MonoBehaviour
{
    [Header("ROBOT")]
    public OmniRobot robot;

    [Header("PRAYA LABS API")]
    public string apiKey;

    private void Start()
    {
        robot.SetApiKey(apiKey);
        robot.StartApiReader();
    }

    private void Update()
    {
        if (robot.GetBool("north") == true)
            robot.North();

        else if (robot.GetBool("south") == true)
            robot.South();

        else if (robot.GetBool("northwest") == true)
            robot.NorthWest();

        else if (robot.GetBool("southeast") == true)
            robot.SouthEast();

        else if (robot.GetBool("cw") == true)
            robot.Clockwise();

        else if (robot.GetBool("ccw") == true)
            robot.CounterClockwise();

        else
            robot.Stop();
    }

    private void OnDisable()
    {
        if (robot != null)
            robot.StopApiReader();
    }
}
