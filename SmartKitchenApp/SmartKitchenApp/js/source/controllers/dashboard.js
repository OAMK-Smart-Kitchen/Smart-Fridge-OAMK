app.controller('dashboard', [
    '$scope',
    '$location',
    '$rootScope',
    'geolocation',
    function ($scope, $location, $rootScope, geolocation) {

        /*
        Stap1: functie Init
        --------------------
        */

        // hier kan je zaken doen die ALTIJD moeten gebeuren bij het inladen van deze pagina, bijvoorbeeld: config ophalen, user checken en ophalen, een of andere call naar service met info... getNumberOfRegisterdUsers ofzo...

        var init = function () {
            console.log('dashboard controller started');
            
        };

        /*
        Stap2: Controller vars (niet in scope!)
        ------------------------------------------
        */
        


        /*
        Stap3: Controller functions (niet in scope!)
        --------------------------------------------
        */

        var weatherForecast = function () {
            return { monday: "0", tuesday: "2"};
        };
     
        /*
        Stap4: Scope vars
        ------------------
        */

        $scope.coords = geolocation.getLocation().then(function (data) {
            console.log("LAT: " + data.coords.latitude);
            console.log("LONG: " + data.coords.longitude);
            return { lat: data.coords.latitude, long: data.coords.longitude };
        });

        $scope.weather = weatherForecast();

        /* Stap5: Scope functions
        -------------------------
        */
        

       
        /* Stap6: init aanroepen
        --------------------
        */
        init();

    }]);