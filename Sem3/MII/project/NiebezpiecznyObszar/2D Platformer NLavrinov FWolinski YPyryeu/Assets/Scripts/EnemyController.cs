using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyController : MonoBehaviour
{
    [Range(0.01f, 20.0f)][SerializeField] private float moveSpeed = 4.5f; // moving speed of the enemy
    [SerializeField] private float moveRange = 1.0f;
    
    private float startPositionX;

    private Animator animator;
    private bool isFacingRight = false;
    private bool isMovingRight = false;

    private bool isDead = false;

    void Awake()
    {
        // rigidBody = GetComponent<Rigidbody2D>();
        animator = GetComponent<Animator>();
        startPositionX = this.transform.position.x;
    }

    private void Flip()
    {
        isFacingRight = !isFacingRight;
        Vector3 scale = transform.localScale;

        scale.x *= -1;

        transform.localScale = scale;
    }

    void MoveRight()
    {
        // isWalking = true;

        if (isFacingRight != true)
        {
            Flip();
        }
        transform.Translate(moveSpeed * Time.deltaTime, 0.0f, 0.0f, Space.World);
        // rigidBody.velocity = new Vector2(moveSpeed, rigidBody.velocity.y);
    }
    void MoveLeft()
    {
        // isWalking = true;

        if (isFacingRight == true)
        {
            Flip();
        }
        transform.Translate(-moveSpeed * Time.deltaTime, 0.0f, 0.0f, Space.World);
        // rigidBody.velocity = new Vector2(moveSpeed, rigidBody.velocity.y);
    }

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (isMovingRight){
            if(this.transform.position.x <= startPositionX + moveRange) 
            {
                MoveRight();
            }
            else 
            {
                isMovingRight = false;
            }
        }else {
            if(this.transform.position.x >= startPositionX - moveRange) 
            {
                MoveLeft();
            }
            else 
            {
                isMovingRight = true;
            }
        }
    }

    void OnTriggerEnter2D(Collider2D other)
    {
        isDead = true;
    }
}
