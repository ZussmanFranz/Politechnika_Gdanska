<?php
use MongoDB\Operation\InsertOne;

require './vendor/autoload.php';


function get_db()
{
    $mongo = new MongoDB\Client(
        "mongodb://localhost:27017/wai",
        [
            'username' => 'wai_web',
            'password' => 'w@i_w3b',
        ]);

    $db = $mongo->wai;

    return $db;
}

function create_user($login, $password, $email)
{
    $db = get_db();

    $new_user = [
        'login' => $login,
        'password' => $password,
        'email' => $email
    ];

    $query = [
        'login' => $login,
        'password' => $password,
        'email' => $email
    ];

    $exists = $db->users->findOne($query); //sprawdza, czy już istnieje

    if ($exists) {
        return 0;
    } else {
        $db->users->insertOne($new_user);
        return 1;
    }
}

function login_check($login)
{
    $db = get_db();
    $result = $db->users->findOne(["login" => $login]);

    if ($result == null)
    {
        return true;
    }
    else{
        return false;
    }
}

function db_upload_image($name, $author, $title, $private)
{
    $db = get_db();

    $new_image = [
        'name' => $name,
        'author' => $author,
        'title' => $title,
        'private' => $private
    ];

    $db->images->insertOne($new_image);
}

function db_get_images($login, $page, $page_size)
{
    $db = get_db();

    $opts = [
        'skip' => (int)($page * $page_size),
        'limit' => $page_size
    ];
    $filter = [
        '$or' => [
            ['private' => 'no'],
            ['$and' => [['private' => 'yes'], ['author' => $login]]]
        ]
    ];

    $images = $db->images->find($filter, $opts);
    
    return $images;
}

function db_count_pages($page_size, $login)
{
    $db = get_db();

    $filter = [
        '$or' => [
            ['private' => 'no'],
            ['$and' => [['private' => 'yes'], ['author' => $login]]]
        ]
    ];

    $images = $db->images->find($filter);

    $count_images = 0;

    foreach ($images as $image)
    {
        $count_images++;
    }

    if ($count_images <= $page_size)
    {
        return 0;
    }
    else
    {
        $count_pages = floor($count_images / $page_size);
    }

    return $count_pages;
}

function check_image($image)
{
    //sprawdza, czy plik jest zdjęciem
    $check = getimagesize($_FILES['image']['tmp_name']);
    if ($check === false) {
        return "File is not an image or it's extension is not supported.";
    }

    if ($_FILES['image']['size'] > 1000000) {
        return "File size must be lover then 1MB";
    }

    $fileExtension = strtolower(pathinfo($_FILES['image']['name'], PATHINFO_EXTENSION));
    if (($fileExtension != 'jpg') && ($fileExtension != 'png')) {
        return "Sorry, only JPG and PNG files are allowed.";
    }

    return "OK";
}

function Watermark($sourceImagePath, $outputImagePath, $text, $type) {

    if(($type == 'image/jpg') || ($type == 'image/jpeg'))
    {
        $sourceImage = imagecreatefromjpeg($sourceImagePath);  
    }
    else
    {
        $sourceImage = imagecreatefrompng($sourceImagePath); 
    } 

    $textColor = imagecolorallocate($sourceImage, 255, 0, 255); 
    $fontSize = 30;

    $x = 10; // pozycja znaku wodnego
    $y = 20; // 

    
    imagestring($sourceImage, $fontSize, $x, $y, $text, $textColor);


    if(($type == 'image/jpg') || ($type == 'image/jpeg'))
    {
        imagejpeg($sourceImage, $outputImagePath); 
    }
    else
    {
        imagepng($sourceImage, $outputImagePath); 
    } 

    imagedestroy($sourceImage);
}

function Miniature($sourceImagePath, $outputImagePath, $width, $height, $type) {
    
    if(($type == 'image/jpg') || ($type == 'image/jpeg'))
    {
        $sourceImage = imagecreatefromjpeg($sourceImagePath);  
    }
    else
    {
        $sourceImage = imagecreatefrompng($sourceImagePath); 
    }

    $originalWidth = imagesx($sourceImage);
    $originalHeight = imagesy($sourceImage);

    $aspectRatio = $width / $height;
    $aspectRatio_before = $originalWidth / $originalHeight;

    $newWidth = $width;
    $newHeight = $height;

    if ($aspectRatio_before > $aspectRatio)
    {
        //szerokość trzeba obciąć
        $newWidth = $newHeight * $aspectRatio_before;
        $width_crop = $newWidth - $width;
    }
    elseif($aspectRatio_before < $aspectRatio)
    {
        //wysokość trzeba obciąć
        $newHeight = $newWidth / $aspectRatio_before;
        $height_crop = $newHeight - $height;
    }
    //jeżeli żaden z warunków nie zachodzi, to wszystko w porządku

    $miniature = imagecreatetruecolor($newWidth, $newHeight);
    imagecopyresampled($miniature, $sourceImage, 0, 0, 0, 0, $newWidth, $newHeight, $originalWidth, $originalHeight);

    if(isset($width_crop))
    {
        $miniature = imagecrop($miniature, ['x' => ($width_crop / 2), 'y' => 0, 'width' => $width, 'height' => $height]);
    }
    elseif(isset($height_crop))
    {
        $miniature = imagecrop($miniature, ['x' => 0, 'y' => ($height_crop/2), 'width' => $width, 'height' => $height]);
    }

    if(($type == 'image/jpg') || ($type == 'image/jpeg'))
    {
        imagejpeg($miniature, $outputImagePath); 
    }
    else
    {
        imagepng($miniature, $outputImagePath); 
    }

    imagedestroy($sourceImage);
    imagedestroy($miniature);
}

function server_upload_image($image, $watermark) {
    $targetDirectory = "./images/originals/";
    $watermarkDirectory = "./images/watermarks/";
    $miniatureDirectory = "./images/miniatures/";

    $fileName = $image['name'];
    $tempFilePath = $image['tmp_name'];

    move_uploaded_file($tempFilePath, $targetDirectory . $fileName);

    Watermark($targetDirectory . $fileName, $watermarkDirectory . $fileName, $watermark, $image['type']);

    Miniature($targetDirectory . $fileName, $miniatureDirectory . $fileName, 200, 125, $image['type']);
}
