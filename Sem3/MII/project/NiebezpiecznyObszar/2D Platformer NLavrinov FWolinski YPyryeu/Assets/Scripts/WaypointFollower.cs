using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WaypointFollower : MonoBehaviour
{
    [SerializeField] private GameObject[] waypoints;
    private int current_waypoint = 0;
    [SerializeField] private float speed = 4.0f;

    void Awake()
    {
        Debug.Log("Waypoint platform spawned!\nCurrent waypoint: " + current_waypoint);
        Debug.Log("Number of waypoints: " + waypoints.Length);
        for (int i = 0; i < waypoints.Length; i++){
            Debug.Log("Waypoint: " + waypoints[i].transform.position);
        }
    }


    // Update is called once per frame
    void Update()
    {
        float distance = Vector2.Distance(transform.position, waypoints[current_waypoint].transform.position);

        if (distance <= 0.1f){
            current_waypoint = (current_waypoint + 1) % waypoints.Length;
        }

        transform.position = Vector2.MoveTowards(transform.position, waypoints[current_waypoint].transform.position, speed * Time.deltaTime);
    }
}
