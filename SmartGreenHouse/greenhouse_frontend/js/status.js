$(document).ready(function() {
  var status;
  $.ajax({
    url: 'http://127.0.0.1:8080/api/data',
    type: 'GET',
    success: function(response){
      status = response.status;
      populateStatus();
    }
  });

  setInterval(update, 5000);

  function update(){
    $.ajax({
      url: 'http://127.0.0.1:8080/api/data',
      type: 'GET',
      success: function(response){
        status = response.status;
        populateStatus();
      }
    });
  }

  function populateStatus(){
    if(status == "auto"){
      $('.status-text').html('<div class="status-item"><p><i class="fas fa-sliders-h"></i> Automatico </p></div>');
      $('.status-item').css('background-color', 'rgba(123,185,0,0.5)').css('border', '1px solid green');
    }
    else if(status == "manual"){
      $('.status-text').html('<div class="status-item"><p><i class="fas fa-hand-point-up"></i> Manuale </p></div>')
      $('.status-item').css('background-color', 'rgba(185, 31, 0, 0.4)').css('border', '1px solid red');
    }
  }

});
