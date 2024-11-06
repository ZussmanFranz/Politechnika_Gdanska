<?php

require 'AJAX.php';

if($_SERVER['REQUEST_METHOD'] === 'POST' ){
    
  if (isset($_POST['E_typ']))
  {
    //typ jest wybrany => tylko AJAX
    echo robAJAX($_POST['E_typ']);
    exit;
  }
  elseif( (isset($_FILES["EmotiFile"])) && (isset($_POST['radio-1'])) )
  {
    //plik i typ emotkowy są ustalone
    //echo "tu będzie odbiór pliku";
    if ($_FILES["EmotiFile"]["error"] == UPLOAD_ERR_OK ){
        // plik przeszedł poprawnie i typ emotki ustawiony
        //echo "plik w katalogu tymczasowym uploadu";
        //echo '<pre> Here is some more debugging info:<br >';
        //print_r($_FILES);
        //print "</pre>";
        //$uploaddir = '/var/www/dev/src/web/LAB2_PHP1/';
        $uploaddir = $_SERVER['DOCUMENT_ROOT'];
        $uploadfile = $uploaddir . basename($_FILES['EmotiFile']['name']);

        if($_POST['radio-1'] == "P")
        {
            $uploaddir = $uploaddir . '/E_positive';
        }
        else {
            $uploaddir = $uploaddir . '/E_negative';
        }

        echo $uploaddir;

        if(move_uploaded_file($_FILES['EmotiFile']['tmp_name'] ,$uploadfile))
        {
            echo "Plik przesłany poprawnie \n";
        }
        else 
        {
            echo "Possible file upload attack!\n";
        }
    }
    else {
        //plik załączono ale jest problem z jego przesłaniem
        echo "Jest problem z tym plikiem <a
        href='EmotiUpload.php' >Wróć</a>";
    }
  }
  else
  {
    echo 'Wyberz parametry <a href="EmotiUpload.php"> Wróć </a>';
    exit;
  }
}
else{
    //metoda GET
    include 'Nagl.php';
}

?>


<body>
  <section >
      <fieldset>
          <legend>Typ emotki: </legend>
          <label for="radio-1">Pozytywne</label>
          <input type="radio" name="radio-1" id="radio-1" onchange="wybor(this);" value="P">
          <label for="radio-2">Negatywne</label>
          <input type="radio" name="radio-1" id="radio-2" onchange="wybor(this);" value="N">
      </fieldset>
  </section> 

  <form enctype="multipart/form-data" action="EmotiUpload.php" method="POST">
    <input type="hidden" name="MAX_FILE_SIZE" value="30000" />
      <!-- Name input’a jest nazwą w tablicy $_FILES -->
      Wskaż plik emotiki: <input name="EmotiFile" type="file"/>
    <input type="submit" value="Send File" />
  </form>

  <div id="result"> 
  </div>
 

  <script>
  $( function() {
    $( "input" ).checkboxradio();
  } );
  
  function wybor(param){
    $.ajax({
      method:"POST",
      url: "Emoti2.php",
      data: {E_typ:param.value} //wartość z inputa typu radio
    }).done(function(msg){
      $("#result").html(msg);
    });
	
  };
  </script>
</body>
</html>