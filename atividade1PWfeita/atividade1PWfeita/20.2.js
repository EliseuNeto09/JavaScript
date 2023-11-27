var listas = document.getElementsByTagName("ul");
var segundaList = listas [1];
var Secundariodata = segundaList.getElementsByTagName("li");
document.write("<p>Há "+Secundariodata.length+"  elementos na segunda lista" );
for (var i = 0; i < Secundariodata.length; i++) {
document.write("<p>" + Secundariodata[i].innerHTML + "</p>");
}
