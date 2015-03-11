app.controller('dashboard', [
    '$scope',
    '$location',
    '$rootScope',
    'geolocation',
    'weatherservice',
    function ($scope, $location, $rootScope, geolocation, weatherservice) {

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
                           $scope.weather = angular.fromJson(data);;
                           console.log($scope.weather);

                       });
                });

            };
        };

        /*
        Stap4: Scope vars
        ------------------
        */

        $scope.weather;

        /* Stap5: Scope functions
        -------------------------
        */



        /* Stap6: init aanroepen
        --------------------
        */
        init();

    }]);