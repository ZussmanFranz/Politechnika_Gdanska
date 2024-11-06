using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlatformMoving : MonoBehaviour
{
    [Header( "Movement parameters" )]
    [Range(0.01f, 20.0f)][SerializeField] private float moveSpeed = 4.5f; // moving speed of the platform
    [SerializeField] private float moveRange = 1.0f;
    [Range(0.0f, 90.0f)][SerializeField] private float alfa = 0.0f; // moving angle of the platform
    

    
    private Vector3 startPosition;

    private bool isMovingRight = false;

    private Rigidbody2D rigidBody;

    void Awake()
    {
        rigidBody = GetComponent<Rigidbody2D>();
        startPosition = this.transform.position;
    }


    // Update is called once per frame
    void Update()
    {
        float distance = Vector2.Distance(startPosition, transform.position);

        if (distance >= moveRange){
            moveSpeed *= -1;
        }

        transform.Translate((float)Math.Cos(alfa * Math.PI / 180) * moveSpeed * Time.deltaTime, (float)Math.Sin(alfa * Math.PI / 180) * moveSpeed * Time.deltaTime, 0.0f, Space.World);
    }
}
