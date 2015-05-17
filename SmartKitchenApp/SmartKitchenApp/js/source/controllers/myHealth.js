app.controller('myhealth', [
    '$scope',
    '$location',
    '$rootScope',
    function ($scope, $location, $rootScope) {

        /*
        Stap1: functie Init
        --------------------
        */

        var init = function () {
            console.log("My Health controller started");
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

        $scope.MyPoints = $rootScope.activeMember.GamePoints;

        /* Stap5: Scope functions
        -------------------------
        */

        $scope.goToBMI = function () {
            console.log("Navigate to My BMI");
            $location.path("/dashboard/myhealth/bmi");
        };

        $scope.goToPoints = function () {
            console.log("Navigate to My Points");
            $location.path("/dashboard/myhealth/points");
        };

        /* Stap6: init aanroepen
        --------------------
        */
        init();

    }]);