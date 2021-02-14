$(document).ready(function(){
	var color = Chart.helpers.color;
	var config;
	var irrigation = [];
	var time = [];
	var timeLaps = "";

	config = {
			type: 'line',
			data: {
				datasets: [{
					label: 'Irrigation',
					backgroundColor: 'rgba(66, 134, 244, 0.2)',
					borderColor: 'rgb(66, 134, 244)',
					fill: true,
					pointHoverRadius: 10,
					data: [],
				}]
			},
			options: {
				responsive: true,
				title: {
					display: true,
					text: 'Irrigation'
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
							labelString: 'Irrigation L/min',
							fontStyle: 'bold',
						},
						ticks: {
							suggestedMin: 0,
							suggestedMax: 35,
            }
					}]
				}
			}
		};

		$.ajax({
			url: "http://127.0.0.1:8080/api/data",
			type: "GET",
			success: function(response){
				var irr = response.irrigation;
				for(var i = 0; i < irr.length; i++){
					irrigation[i] = irr[i].value;
					time[i] = irr[i].time;
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
				var irr = response.irrigation;
				irrigation = [];
				time = [];
				for(var i = 0; i < irr.length; i++){
					irrigation[i] = irr[i].value;
					time[i] = irr[i].time;
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
					x: dateJson, y: irrigation[i]
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
					x: dateJson, y: irrigation[i]
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
					x: dateJson, y: irrigation[i]
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
				x: dateJson, y: irrigation[i]
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
				x: dateJson, y: irrigation[i]
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
				x: dateJson, y: irrigation[i]
			});
	}
	window.myLine.update();
	if(config.data.datasets[0].data.length == 0){
		$('h2').html("Nessun dato registrato");
	}
}


	function populateData(){
		$('#irrigation-last-hour').click(setHour);
		$('#irrigation-last-day').click(setDay);
		$('#irrigation-last-week').click(setWeek);
		$('#irrigation-last-month').click(setMonth);
		$('#irrigation-last-year').click(setYear);
		$('#irrigation-ever').click(setEver);
	}

function createGraphs(){
			var ctx = document.getElementById('irrigation').getContext('2d');
			window.myLine = Chart.Line(ctx, config);

	}

	function destroyGraphs(){
		window.myLine.destroy();
	}

	$('#irrigazione').click(function(){
		showModal();
		createGraphs();
	});

	$('.irrigation-modal-close').click(function() {
		hideModal();
		destroyGraphs();
		timeLaps = "";
	});

	function showModal(){
		$('.irrigation-modal').css('visibility', 'visible');
		$('.irrigation-modal').css('opacity', '1');
	}

	function hideModal(){
		$('.irrigation-modal').css('visibility', 'hidden');
		$('.irrigation-modal').css('opacity', '0');
	}



});
