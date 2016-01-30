$(function(){

	//HTMLを初期化
	$("#out").html("");

	//HTMLを生成
	$.getJSON("test.json", function(data){
		for(var d in data){
			for(var i in data[d])
			$("#out").append('<li>'+i+':'+data[d][i]);
		}
	});
});