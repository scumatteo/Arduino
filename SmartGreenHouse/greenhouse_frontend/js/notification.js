$(document).ready(function(){
	var color = Chart.helpers.color;
  var number;
	var time = [];
	var timeLaps = "";
  var date = [];
  var timeFormat = 'MM/DD/YYYY HH:mm';
	config = {
			type: 'bar',
			data: {
				datasets: [{
					label: 'Notifications',
					backgroundColor: 'rgba(255, 76, 0, 0.2)',
					borderColor: 'rgba(255, 76, 0)',
					borderWidth: 1,
					fill: true,
					data: [],
				}]
			},
			options: {
				responsive: true,
				title: {
					display: true,
					text: 'Notification'
				},
				scales: {
					xAxes: [{
						type: 'time',
						display: true,
						scaleLabel: {
							display: true,
							labelString: 'Time',
							fontStyle: 'bold',
						},
						ticks: {
							major: {
								fontStyle: 'bold',
								fontColor: 'black'
							}
						}
					}],
					yAxes: [{
						display: true,
						scaleLabel: {
							display: true,
							labelString: 'Notification',
							fontStyle: 'bold',
						},
						ticks: {
							suggestedMin: 0,
            }
					}]
				}
			}
		};

		$.ajax({
			url: "http://127.0.0.1:8080/api/data",
			type: "GET",
			success: function(response){
				var not = response.notification;
				for(var i = 0; i < not.length; i++){
					time[i] = not[i].time;
				}

			}
		});

	populateData();
	setInterval(update, 5000);

	function update(){
		$.ajax({
			url: "http://127.0.0.1:8080/api/data",
			type: "GET",
			success: function(response){
        number = [];
				time = [];
				var not = response.notification;
				for(var i = 0; i < not.length; i++){
					time[i] = not[i].time;
				}
				if(timeLaps == "hour")
					setHour();
				else if(timeLaps == "day")
					setDay();
				else if(timeLaps == "week")
					setWeek();
				else if(timeLaps == "month")
					setMonth();
				else if(timeLaps == "year")
					setYear();
				else if(timeLaps == "ever")
					setEver();
				}
		});
	}

	function setHour(){
    date = [];
    number = [];
    for(var i = 0; i < 60; i++){
      number.push(0);
    }
		timeLaps = "hour";
		$('h2').html("");
		config.data.datasets[0].data = [];
    var now = new moment();
		for(var i = 0; i < time.length; i++){
			var dateJson = new moment(time[i], moment.ISO_8601);
			if(dateJson.hour() === now.hour() && dateJson.day() === now.day() && dateJson.month() === now.month() && dateJson.year() === now.year()){
        number[dateJson.minute()]++;
        date.push(dateJson);
			}
		}
    for(var i = 0; i < 60; i++){
      now.minute(i);
      config.data.datasets[0].data.push({
        x: now.format(timeFormat), y: number[i]
      });
		}
		window.myBar.update();
		if(config.data.datasets[0].data.length == 0){
			$('h2').html("Nessun dato registrato");
		}
	}

	function setDay(){
    date = [];
    number = [];
    for(var i = 0; i < 24; i++){
      number.push(0);
    }
		timeLaps = "day";
		$('h2').html("");
		config.data.datasets[0].data = [];
    var now = new moment();
		for(var i = 0; i < time.length; i++){
			var dateJson = new moment(time[i], moment.ISO_8601);
			if(dateJson.day() === now.day() && dateJson.month() === now.month() && dateJson.year() === now.year()){
        number[dateJson.hour()]++;
        date.push(dateJson);
			}
		}
    for(var i = 0; i < 24; i++){
      now.hour(i);
      config.data.datasets[0].data.push({
        x: now.format(timeFormat), y: number[i]
      });
		}
		window.myBar.update();
		if(config.data.datasets[0].data.length == 0){
			$('h2').html("Nessun dato registrato");
		}
	}

	function setWeek(){
    date = [];
    number = [];
    for(var i = 0; i < 7; i++){
      number.push(0);
    }
		timeLaps = "week";
		$('h2').html("");
    var now = new moment();
		config.data.datasets[0].data = [];
		for(var i = 0; i < time.length; i++){
			var dateJson = new moment(time[i], moment.ISO_8601);
			if(dateJson.week() === now.week() && dateJson.year() === now.year()){
        number[dateJson.day()]++;
        date.push(dateJson);
			}
		}
    for(var i = 0; i < 7; i++){
      now.day(i);
      config.data.datasets[0].data.push({
        x: now.format(timeFormat), y: number[i]
      });
    }
		window.myBar.update();
		if(config.data.datasets[0].data.length == 0){
			$('h2').html("Nessun dato registrato");
		}
	}

function setMonth(){
  var now = new moment();
  date = [];
  number = [];
  for(var i = 0; i < now.daysInMonth(); i++){
    number.push(0);
  }
	timeLaps = "month";
	$('h2').html("");
	config.data.datasets[0].data = [];
	for(var i = 0; i < time.length; i++){
		var dateJson = new moment(time[i], moment.ISO_8601);
		if(dateJson.month() === now.month() && dateJson.year() === now.year()){
      number[dateJson.date()]++;
      date.push(dateJson);
		}
	}

  for(var i = 1; i <= now.daysInMonth(); i++){
    now.date(i);
    config.data.datasets[0].data.push({
      x: now.format(timeFormat), y: number[i]
    });
  }
	window.myBar.update();
	if(config.data.datasets[0].data.length == 0){
		$('h2').html("Nessun dato registrato");
	}
}

function setYear(){
  date = [];
  number = [];
  for(var i = 0; i < 12; i++){
    number.push(0);
  }
	timeLaps = "year";
	$('h2').html("");
	config.data.datasets[0].data = [];
  var now = new moment();
	for(var i = 0; i < time.length; i++){
		var dateJson = new moment(time[i], moment.ISO_8601);
		if(dateJson.year() === now.year()){
      number[dateJson.month()]++;
      date.push(dateJson);
		}
	}
  for(var i = 0; i < 12; i++){
    now.month(i);
    config.data.datasets[0].data.push({
      x: now.format(timeFormat), y: number[i]
    });
  }
	window.myBar.update();
	if(config.data.datasets[0].data.length == 0){
		$('h2').html("Nessun dato registrato");
	}
}

function setEver(){
  date = [];
  number = [];
	timeLaps = "ever";
	$('h2').html("");
	config.data.datasets[0].data = [];
  var now = new moment();
  var data = new moment();
	var min = new moment(time[0], moment.ISO_8601);
	for(i = 0; i <= now.year() - min.year() + 2 ; i++){
		number.push(0);
	}
	for(var i = 0; i < time.length; i++){
		var dateJson = new moment(time[i], moment.ISO_8601);
      number[now.year() - dateJson.year() + 1]++;
      date.push(dateJson);

	}
  for(var i = 0; i < number.length; i++){
    data.year(now.year() - i + 1);
    config.data.datasets[0].data.push({
      x: data.format(timeFormat), y: number[i]
    });
  }
	window.myBar.update();
	if(config.data.datasets[0].data.length == 0){
		$('h2').html("Nessun dato registrato");
	}
}


	function populateData(){
		$('#notification-hour').click(setHour);
		$('#notification-day').click(setDay);
		$('#notification-week').click(setWeek);
		$('#notification-month').click(setMonth);
		$('#notification-year').click(setYear);
		$('#notification-ever').click(setEver);
	}

function createGraphs(){
			var ctx = document.getElementById('notification').getContext('2d');
			window.myBar = new Chart(ctx, config);

	}

	function destroyGraphs(){
		window.myBar.destroy();
	}

	$('#segnalazioni').click(function(){
		showModal();
		createGraphs();
	});

	$('.notification-modal-close').click(function() {
		hideModal();
		destroyGraphs();
		timeLaps = "";
	});

	function showModal(){
		$('.notification-modal').css('visibility', 'visible');
		$('.notification-modal').css('opacity', '1');
	}

	function hideModal(){
		$('.notification-modal').css('visibility', 'hidden');
		$('.notification-modal').css('opacity', '0');
	}



});
