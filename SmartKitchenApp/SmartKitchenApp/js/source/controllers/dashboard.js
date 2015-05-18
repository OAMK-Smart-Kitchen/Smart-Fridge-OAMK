app.controller('dashboard', [
    '$scope',
    '$location',
    '$rootScope',
    'geolocation',
    'weatherservice',
    '$q',
    function ($scope, $location, $rootScope, geolocation, weatherservice, $q) {

        /*
        Stap1: functie Init
        --------------------
        */

        // hier kan je zaken doen die ALTIJD moeten gebeuren bij het inladen van deze pagina, bijvoorbeeld: config ophalen, user checken en ophalen, een of andere call naar service met info... getNumberOfRegisterdUsers ofzo...

        var init = function () {
            console.log('dashboard controller started');
            getWeatherForecast();
        };

        /*
        Stap2: Controller vars (niet in scope!)
        ------------------------------------------
        */


        /*
        Stap3: Controller functions (niet in scope!)
        --------------------------------------------
        */



        var getWeatherForecast = function () {
            var lati = 0; var longi = 0;
            if (navigator.geolocation) {
                navigator.geolocation.getCurrentPosition(function (position) {
                    lati = position.coords.latitude;
                    longi = position.coords.longitude;
                    console.log(lati);
                    console.log(longi);
                    weatherservice.getWeather(lati, longi)
                       .then(function (data) {
                           var weather = angular.fromJson(data);
                           
                           var tempArr = [];
                           //console.log(weather);
                           for (var i = 0; i < 6; i++) {
                               var resMinF = weather.daily.data[i].temperatureMin;
                               var resMaxF = weather.daily.data[i].temperatureMax;
                               var resMinC = Math.round(((resMinF - 32) / 1.8) * 10) / 10;
                               var resMaxC = Math.round(((resMaxF - 32) / 1.8) * 10) / 10;
                               var resTimeUnix = weather.daily.data[i].time; //GMT+2 -> 3600 (1h) * 2 = 7200

                               var d = new Date();
                               d.setSeconds(resTimeUnix);
                               
                               var weekday = new Array(7);
                               weekday[0] = "Sunday";
                               weekday[1] = "Monday";
                               weekday[2] = "Tuesday";
                               weekday[3] = "Wednesday";
                               weekday[4] = "Thursday";
                               weekday[5] = "Friday";
                               weekday[6] = "Saturday";

                               var resTimeDay = weekday[d.getDay()];

                               tempArr.push({ 'min': "" + resMinC + "", 'max': "" + resMaxC + "", 'day': "" + resTimeDay + "" });
                           }
                           $scope.forecast = tempArr;
                           //console.log($scope.forecast);
                           $scope.$apply();
                       });
                });

            };
        };

        /*
        Stap4: Scope vars
        ------------------
        */

        $scope.fridgeTemp = app.CurrentKitchen.TemperatureFridge;

        /* Stap5: Scope functions
        -------------------------
        */

        $scope.goToHealthGame = function () {
            console.log("NOT AVAILABLE");
        };

        $scope.goToMyHealth = function () {
            console.log("Navigate to My Health");
            $location.path("/dashboard/myhealth");
        };

        $scope.goToMyProfile = function () {
            console.log("Navigate to My Profile");
            $location.path("/dashboard/myprofile");
        };

        $scope.goToShoppingBag = function () {
            console.log("Navigate to Shoppingbag");
            $location.path("/dashboard/shoppingbag");
        };

        $scope.goToProducts = function () {
            console.log("Navigate to Products");
            $location.path("/dashboard/products");
        };

        $scope.goToRecipes = function () {
            console.log("NOT AVAILABLE");
        };

        /* Stap6: init aanroepen
        --------------------
        */
        init();

    }]);