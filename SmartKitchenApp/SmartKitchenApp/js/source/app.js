var app = angular.module('SmartKitchenApp', ['ngRoute', 'ngResource', 'ui.bootstrap', 'jsonDate', 'typeFilter', 'geolocation']);

//app.serviceUrl = 'http://partibookservice.cloudapp.net/service.svc/';
//app.blobUrl = 'https://partibookservice.blob.core.windows.net/images/';
app.CryptoJS = function (message) {
    return CryptoJS.SHA256(message);
}

//dataTemplates
//Teacher Object
app.Member = function () {
    this.Id = null;
    this.Username = null;
    this.FirstName = null;
    this.Lastname = null;
    this.Email = null;
    this.Password = null;
};
app.CurrentMember = new app.Member();
//Lesson Object
app.Lesson = function () {
    this.Id = null;
    this.Name = null;
    this.CreationDate = null;
    this.RevisionDate = null;
    this.IsActive = null;
    this.Token = null;
    this.Teacher_Id = null;
}
app.CurrentLesson = new app.Lesson();
//Question Object
app.Question = function () {
    this.Id = null;
    this.Text = null;
    this.Image = null;
    this.IsActive = null;
    this.QuestionType = null;
    this.Lesson_Id = null;
    this.ImageString = null;
}
app.CurrentQuestion = new app.Question();
//PossibleAnswer Object
app.PossibleAnswer = function () {
    this.Id = 0;
    this.Text = null;
    this.Image = null;
    this.IsCorrect = false;
    this.Question_Id = null;
    this.AnswerImage = null;
}
app.CurrentPossibleAnswer = new app.PossibleAnswer();
//CollectedAnswer Object
app.CollectedAnswer = function () {
    this.Firstname = null;
    this.Lastname = null;
    this.Answer = null;
    this.AnswerImage = null;
    this.Token = null;
    this.Question_Id = null;
    this.AnswerImageString = null;
}
//Type Enum
app.TypeEnum = {
    Test1: 0,
    Test2: 1,
    Test3: 2,
    Test4: 3
};

//FILTERS
app.filter('slice', function () {
    return function (arr, start, end) {
        return arr.slice(start, end);
    };
});