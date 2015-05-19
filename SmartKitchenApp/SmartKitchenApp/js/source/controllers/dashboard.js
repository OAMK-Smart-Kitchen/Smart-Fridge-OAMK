app.controller('dashboard', [
    '$scope',
    '$location',
    '$rootScope',
    'geolocation',
    '$sce',
    '$q',
    function ($scope, $location, $rootScope, geolocation, $sce, $q) {

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
            if (navigator.geolocation) {
                navigator.geolocation.getCurrentPosition(function (position) {
                    $scope.lati = position.coords.latitude;
                    $scope.longi = position.coords.longitude;
                    console.log($scope.lati);
                    console.log($scope.longi);
                });
            } else {
                $scope.lati = 65.000065;
                $scope.longi = 25.5097513;
            }

            var fcUrl = "http://forecast.io/embed/#lat=" + $scope.lati + "&lon=" + $scope.longi + "&color=#2c3e50&font=sans-serif&units=ca";
            $scope.ForecastEmbedUrl = $sce.trustAsResourceUrl(fcUrl);
        };

        /*
        Stap4: Scope vars
        ------------------
        */

        $scope.fridgeTemp = app.CurrentKitchen.TemperatureFridge;
        $scope.lati = 65.000065;
        $scope.longi = 25.5097513;
        $scope.ForecastEmbedUrl = null;

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