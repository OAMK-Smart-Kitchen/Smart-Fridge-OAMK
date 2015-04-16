var basePath = 'js/source/templates/';

window.routes =
{
    //NO LOGIN REQUIRED
    "/": {
        templateUrl: basePath + 'homepage.html',
        requireLogin: false
    },

    "/get-started": {
        templateUrl: basePath + 'get_started.html',
        requireLogin: false
    },

    "/login": {
        templateUrl: basePath + 'login.html',
        requireLogin: false
    },

    "/about": {
        templateUrl: basePath + 'about.html',
        requireLogin: false
    },

    // LOGIN REQUIRED
    "/dashboard": {
        templateUrl: basePath + 'dashboard/dashboard.html',
        requireLogin: true
    },

    "/members": {
        templateUrl: basePath + 'dashboard/members.html',
        requireLogin: true
    },

    "/dashboard/myprofile": {
        templateUrl: basePath + 'dashboard/myprofile.html',
        requireLogin: true
    },

    "/dashboard/myhealth": {
        templateUrl: basePath + 'dashboard/myhealth.html',
        requireLogin: true
    },

    "/dashboard/myhealth/bmi": {
        templateUrl: basePath + 'dashboard/mybmi.html',
        requireLogin: true
    },

    "/dashboard/myhealth/points": {
        templateUrl: basePath + 'dashboard/mypoints.html',
        requireLogin: true
    },

    "/dashboard/shoppingbag": {
        templateUrl: basePath + 'dashboard/shoppingbag.html',
        requireLogin: true
    },

    "/dashboard/products": {
        templateUrl: basePath + 'dashboard/products.html',
        requireLogin: true
    }
};

app.config(function ($routeProvider) {

    //this loads up our routes dynamically from the previous object 
    for (var path in window.routes) {
        $routeProvider.when(path, window.routes[path]);
    }
    $routeProvider
    .otherwise({
        templateUrl: basePath + '404Template.html',
        requireLogin: false
    });

})
.run(function ($rootScope, $location) { //Add the service where the data is stored to check if logged in yet

    $rootScope.$on("$locationChangeStart", function (event, next, current) {

        //var urlArray = next.split("index.html#");
        var urlArray = next.split("#");
        var routeName = urlArray[1];

        if (window.routes[routeName].requireLogin == true) {
            if (app.CurrentMember.Id == undefined) { //Check on service if logged in yet.
                $location.path('/');
                //event.preventDefault();
            }
        }
    });

});