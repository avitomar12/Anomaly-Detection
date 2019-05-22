var chart;

/**
 * Request data from the server, add it to the graph and set a timeout
 * to request again
 */
function requestData() {
    $.ajax({
        url: '/live-data',
        success: function(points) {
            var series = chart.series[0],
                shift = series.data.length > 20; // shift if the series is
var z_axis=[points[0],points[3]];
var y_axis=[points[0],points[2]];
 var x_axis= [points[0],points[1]] ;                                               // longer than 20
         // add the point
            chart.series[0].addPoint(x_axis, true, shift);
	chart.series[1].addPoint(y_axis,true,shift);
	chart.series[2].addPoint(z_axis,true,shift);
            // call it again after one second
            setTimeout(requestData, 1000);
        },
        cache: false
    });
}

$(document).ready(function() {
    chart = new Highcharts.Chart({
        chart: {
            renderTo: 'data-container',
            defaultSeriesType: 'spline',
            events: {
                load: requestData
            }
        },
        title: {
            text: 'Live Sensor Data'
        },
        xAxis: {
            type: 'time',
            tickPixelInterval: 15,
            maxZoom: 20 * 1000
        },
        yAxis: {
            minPadding: 0.2,
            maxPadding: 0.2,
            title: {
                text: 'Value',
                margin: 80
            }
        },
        series: [{
            name: 'X-axis',
            data: []
        },
	{ name: 'Y-axis',
		data: []
	},
{
 name: 'Z-axis',
  data: []

}]
    });
});
