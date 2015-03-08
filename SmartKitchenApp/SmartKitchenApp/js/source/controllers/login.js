app.controller('login', [
    '$scope',
    '$location',
    '$rootScope',
    function ($scope, $location, $rootScope) {

        /*
        Stap1: functie Init
        --------------------
        */

        // hier kan je zaken doen die ALTIJD moeten gebeuren bij het inladen van deze pagina, bijvoorbeeld: config ophalen, user checken en ophalen, een of andere call naar service met info... getNumberOfRegisterdUsers ofzo...

        var init = function () {
            console.log('login controller started');
        };

        /*
        Stap2: Controller vars (niet in scope!)
        ------------------------------------------
        */


        /*
        Stap3: Controller functions (niet in scope!)
        --------------------------------------------
        */


        /*
        Stap4: Scope vars
        ------------------
        */

        $scope.loginFailed = false;
        $scope.loginStatus = 0;

        /* Stap5: Scope functions
        -------------------------
        */



        //NAVIGATION
        $scope.goToDashboard = function () {
            $location.path("/dashboard/:kitchen.id/member");
            console.log("Navigate to Member Dasboard");
            console.log("Kitchen ID: " + kitchen.id);
        };

        $scope.goToRegister = function () {
            $location.path("/register");
            console.log("Navigate to register");
        };

        /* Stap6: init aanroepen
        --------------------
        */
        init();

    }]);