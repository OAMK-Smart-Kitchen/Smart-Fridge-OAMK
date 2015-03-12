app.controller('dashboard', [
    '$scope',
    '$location',
    '$rootScope',
    'geolocation',
    'weatherservice',
    '$q',
    function ($scope, $location, $rootScope, geolocation, weatherservice,$q) {

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
                           $scope.dailyWeatherTimeZone = weather.timezone;
                           console.log(weather);
                           for (var i = 0; i < 6; i++) {
                               var resMinF = weather.daily.data[i].temperatureMax;
                               var resMaxF = weather.daily.data[i].temperatureMin;
                               var resMinC = Math.round(((resMinF - 32) / 1.8) * 10) / 10;
                               var resMaxC = Math.round(((resMaxF - 32) / 1.8) * 10) / 10;
                               var resTime = weather.daily.data[i].time;
                               $scope.forecast.push({ 'min': "" + resMinC + "", 'max': "" + resMaxC + "", 'time': "" + resTime + "" });
                               //$scope.dailyWeatherTime.push(weather.daily.data[i].time+7200); //GMT+2 -> 3600 (1h) * 2 = 7200
                           }
                           //console.log($scope.dailyWeatherTimeZone);
                           console.log($scope.forecast);
                       });
                });

            };
        };

        /*
        Stap4: Scope vars
        ------------------
        */

        $scope.dailyWeatherTimeZone;
        $scope.forecast = [];

        /* Stap5: Scope functions
        -------------------------
        */



        /* Stap6: init aanroepen
        --------------------
        */
        init();

    }]);