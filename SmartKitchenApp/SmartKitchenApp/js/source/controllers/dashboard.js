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

        //var mysrclat= 0; var mysrclong = 0;

        //$scope.coords = function($scope) {
        //    if (navigator.geolocation) {
        //        navigator.geolocation.getCurrentPosition(function (position) {
        //            mysrclat = position.coords.latitude; 
        //            mysrclong = position.coords.longitude;
        //            console.log(mysrclat);
        //            console.log(mysrclong);
        //        });

        //    }


        //var coords = geolocation.getLocation().then(function (data) {
        //    console.log("LAT: " + data.coords.latitude);
        //    console.log("LONG: " + data.coords.longitude);
        //    return { lat: data.coords.latitude, long: data.coords.longitude };
        //});

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

                           console.log(data);

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