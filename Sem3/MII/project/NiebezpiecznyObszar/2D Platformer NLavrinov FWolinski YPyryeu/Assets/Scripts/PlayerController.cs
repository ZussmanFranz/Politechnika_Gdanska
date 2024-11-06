using System;
using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.SocialPlatforms.Impl;

public class PlayerController : MonoBehaviour
{
    [Header( "Movement parameters" )]
    [Range(0.01f, 20.0f)][SerializeField] private float moveSpeed = 4.5f; // moving speed of the player
    [SerializeField] private float jumpForce = 6.0f;
    private float vertical = 0f;
    private Rigidbody2D rigidBody;
    // private Collider2D myCollider;
    private Animator animator;
    private bool isWalking = false;
    private bool isLadder = false;
    private bool isClimbing = false;
    private int score = 0;
    private int keysFound = 0;
    private int keysNumber = 3;
    private int hearts = 3;

    public LayerMask groundLayer;
    private bool isFacingRight = true;
    const float rayLength = 1.5f;
    bool IsGrounded()
    {
        return Physics2D.Raycast(this.transform.position, Vector2.down, rayLength, groundLayer.value);
    }

    void Jump()
    {
        if (IsGrounded())
        {
            rigidBody.AddForce(Vector2.up * jumpForce, ForceMode2D.Impulse);
            Debug.Log("Jumping");
        }
    }

    void Awake()
    {
        rigidBody = GetComponent<Rigidbody2D>();
        animator = GetComponent<Animator>();
        // myCollider = GetComponent<Collider2D>();
    }

    private void Flip()
    {
        isFacingRight = !isFacingRight;
        Vector3 scale = transform.localScale;

        scale.x *= -1;

        transform.localScale = scale;
    }

    // Update is called once per frame
    void Update()
    {
        // isWalking = false;

        if (Input.GetKey(KeyCode.RightArrow) || Input.GetKey(KeyCode.D))
        {
            isWalking = true;

            if (isFacingRight != true)
            {
                Flip();
            }
            // transform.Translate(moveSpeed * Time.deltaTime, 0.0f, 0.0f, Space.World);
            rigidBody.velocity = new Vector2(moveSpeed, rigidBody.velocity.y);
        }
        else if (Input.GetKey(KeyCode.LeftArrow) || Input.GetKey(KeyCode.A))
        {
            isWalking = true;

            if(isFacingRight != false)
            {
                Flip();
            }
            // transform.Translate(-moveSpeed * Time.deltaTime, 0.0f, 0.0f, Space.World);
            rigidBody.velocity = new Vector2(-moveSpeed, rigidBody.velocity.y);
        }
        else if (Input.GetKeyUp(KeyCode.RightArrow) || Input.GetKeyUp(KeyCode.D) || 
        Input.GetKeyUp(KeyCode.LeftArrow) || Input.GetKeyUp(KeyCode.A))
        {
            isWalking = false;
            rigidBody.velocity = new Vector2(0, rigidBody.velocity.y);
        }

        vertical = Input.GetAxis("Vertical");
        
        if(Math.Abs(vertical) > 0 && isLadder)
        {
            isClimbing = true;
        
        }

        if (Input.GetMouseButtonDown(0) || Input.GetKeyDown(KeyCode.Space))
        {
            Jump();
        }



        Debug.DrawRay(transform.position, rayLength * Vector3.down, Color.white, 1, false);

        animator.SetBool("isGrounded", IsGrounded()); 
        animator.SetBool("isWalking", isWalking); 
    }

    void FixedUpdate()
    {
        if(isClimbing)
        {
            rigidBody.gravityScale = 0.0f;
            rigidBody.velocity = new Vector2(rigidBody.velocity.x, vertical * moveSpeed);
            
        }else{
            rigidBody.gravityScale = 1.0f;
        }
    }

    void OnTriggerEnter2D(Collider2D other)
    {
        switch(other.tag){
            case "Bonus":
                 score += 10;
            
                Debug.Log("Player collected a bonus");
                Debug.Log("Score : " + score);

                other.gameObject.SetActive(false);

                break;
            case "Ladder":
                isLadder = true;
                if(Math.Abs(vertical) > 0)
                {
                    isClimbing = true;
                
                }else{
                    isClimbing = false;
                }

                break;
            case "Key":
                keysFound++;

                Debug.Log("Player collected a key");
                Debug.Log("keysFound : " + keysFound);

                other.gameObject.SetActive(false);

                break;
            case "Heart":
                hearts++;

                Debug.Log("Player collected a heart");
                Debug.Log("hearts : " + hearts);

                other.gameObject.SetActive(false);

                break;
            case "Finish":
                if (keysFound >= keysNumber){
                    Debug.Log("Level finished!");
                }
                else {
                    Debug.Log("You must find all the keys first!");
                }

                break;
            case "MovingPlatform":
                transform.SetParent(other.transform);

                break;
            default:
                Debug.Log("Unrecognised tag");

                break;
        }
    }

    void OnTriggerExit2D(Collider2D other)
    {
        if(other.CompareTag("Ladder"))
        {
            isLadder = false;
            isClimbing = false;
        }

        if(other.CompareTag("MovingPlatform"))
        {
            transform.SetParent(null);
        }
    }
}

