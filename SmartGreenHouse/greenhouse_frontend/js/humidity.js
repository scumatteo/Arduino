$(document).ready(function(){
	var color = Chart.helpers.color;
	var config;
	var humidity = [];
	var time = [];
	var timeLaps = "";

	config = {
			type: 'line',
			data: {
				datasets: [{
					label: 'Humidity',
					backgroundColor: 'rgba(65, 235, 244, 0.2)',
					borderColor: 'rgba(65, 235, 244)',
					fill: true,
					pointHoverRadius: 10,
					data: [],
				}]
			},
			options: {
				responsive: true,
				title: {
					display: true,
					text: 'Humidity'
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
							labelString: 'Humidity %',
							fontStyle: 'bold',
						},
						ticks: {
							suggestedMin: 0,
							suggestedMax: 100,
            }
					}]
				}
			}
		};

		$.ajax({
			url: "http://127.0.0.1:8080/api/data",
			type: "GET",
			success: function(response){
				var hum = response.humidity;
				for(var i = 0; i < hum.length; i++){
					humidity[i] = hum[i].value;
					time[i] = hum[i].time;
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
				var hum = response.humidity;
				humidity = [];
				time = [];
				for(var i = 0; i < hum.length; i++){
					humidity[i] = hum[i].value;
					time[i] = hum[i].time;
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
		timeLaps = "hour";
		$('h2').html("");
		config.data.datasets[0].data = [];
		for(var i = 0; i < time.length; i++){
			var now = new moment();
			var dateJson = new moment(time[i], moment.ISO_8601);
			if(dateJson.hour() === now.hour() && dateJson.day() === now.day() && dateJson.month() === now.month() && dateJson.year() === now.year()){
				config.data.datasets[0].data.push({
					x: dateJson, y: humidity[i]
				});
			}
		}
		window.myLine.update();
		if(config.data.datasets[0].data.length == 0){
			$('h2').html("Nessun dato registrato");
		}
	}

	function setDay(){
		timeLaps = "day";
		$('h2').html("");
		config.data.datasets[0].data = [];
		for(var i = 0; i < time.length; i++){
			var now = new moment();
			var dateJson = new moment(time[i], moment.ISO_8601);
			if(dateJson.day() === now.day() && dateJson.month() === now.month() && dateJson.year() === now.year()){
				config.data.datasets[0].data.push({
					x: dateJson, y: humidity[i]
				});
			}
		}
		window.myLine.update();
		if(config.data.datasets[0].data.length == 0){
			$('h2').html("Nessun dato registrato");
		}
	}

	function setWeek(){
		timeLaps = "week";
		$('h2').html("");
		config.data.datasets[0].data = [];
		for(var i = 0; i < time.length; i++){
			var now = new moment();
			var dateJson = new moment(time[i], moment.ISO_8601);
			if(dateJson.week() === now.week() && dateJson.year() === now.year()){
				config.data.datasets[0].data.push({
					x: dateJson, y: humidity[i]
				});
			}
		}
		window.myLine.update();
		if(config.data.datasets[0].data.length == 0){
			$('h2').html("Nessun dato registrato");
		}
	}

function setMonth(){
	timeLaps = "month";
	$('h2').html("");
	config.data.datasets[0].data = [];
	for(var i = 0; i < time.length; i++){
		var now = new moment();
		var dateJson = new moment(time[i], moment.ISO_8601);
		if(dateJson.month() === now.month() && dateJson.year() === now.year()){
			config.data.datasets[0].data.push({
				x: dateJson, y: humidity[i]
			});
		}
	}
	window.myLine.update();
	if(config.data.datasets[0].data.length == 0){
		$('h2').html("Nessun dato registrato");
	}
}

function setYear(){
	timeLaps = "year";
	$('h2').html("");
	config.data.datasets[0].data = [];
	for(var i = 0; i < time.length; i++){
		var now = new moment();
		var dateJson = new moment(time[i], moment.ISO_8601);
		if(dateJson.year() === now.year()){
			config.data.datasets[0].data.push({
				x: dateJson, y: humidity[i]
			});
		}
	}
	window.myLine.update();
	if(config.data.datasets[0].data.length == 0){
		$('h2').html("Nessun dato registrato");
	}
}

function setEver(){
	timeLaps = "ever";
	$('h2').html("");
	config.data.datasets[0].data = [];
	for(var i = 0; i < time.length; i++){
		var dateJson = new moment(time[i], moment.ISO_8601);

			config.data.datasets[0].data.push({
				x: dateJson, y: humidity[i]
			});
	}
	window.myLine.update();
	if(config.data.datasets[0].data.length == 0){
		$('h2').html("Nessun dato registrato");
	}
}


	function populateData(){
		$('#last-hour').click(setHour);
		$('#last-day').click(setDay);
		$('#last-week').click(setWeek);
		$('#last-month').click(setMonth);
		$('#last-year').click(setYear);
		$('#ever').click(setEver);
	}

function createGraphs(){
			var ctx = document.getElementById('humidity').getContext('2d');
			window.myLine = Chart.Line(ctx, config);

	}

	function destroyGraphs(){
		window.myLine.destroy();
	}

	$('#umidità').click(function(){
		showModal();
		createGraphs();
	});

	$('.humidity-modal-close').click(function() {
		hideModal();
		destroyGraphs();
		timeLaps = "";
	});

	function showModal(){
		$('.humidity-modal').css('visibility', 'visible');
		$('.humidity-modal').css('opacity', '1');
	}

	function hideModal(){
		$('.humidity-modal').css('visibility', 'hidden');
		$('.humidity-modal').css('opacity', '0');
	}



});
