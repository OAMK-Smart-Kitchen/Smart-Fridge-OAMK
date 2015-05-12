var app = angular.module('SmartKitchenApp', ['ngRoute', 'ngResource', 'ui.bootstrap', 'jsonDate', 'typeFilter', 'geolocation', 'datatables']);

app.serviceUrl = 'http://api.verhofstadt.eu/service/';
//app.serviceUrl = 'http://localhost:63666/service/';
//app.blobUrl = 'http://urltopictures.com';
app.CryptoJS = function (message) {
    return CryptoJS.SHA256(message);
}

//dataTemplates
//Member Object
app.Member = function () {
    this.Id = null;
    this.Firstname = null;
    this.Lastname = null;
    this.DateOfBirth = null;
    this.Email = null;
    this.Password = null;
    this.PictureUrl = null;
    this.DefaultColor = null;
    this.Active = null;
    this.GameActivated = null;
    this.GameHealthLevel = null;
    this.GamePoints = null;
    this.Admin = null;
};
app.CurrentMember = new app.Member();
//Kitchen Object
app.Kitchen = function () {
    this.Id = null;
    this.Name = null;
    this.TemperatureFridge = null;
}
app.CurrentKitchen = new app.Kitchen();

//FILTERS
app.filter('slice', function () {
    return function (arr, start, end) {
        return arr.slice(start, end);
    };
});