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
            prepBmi();
        };

        /*
        Stap2: Controller vars (niet in scope!)
        ------------------------------------------
        */

        var lastLength = "XXX";
        var lastWeight = "XX";

        /*
        Stap3: Controller functions (niet in scope!)
        --------------------------------------------
        */

        var calcBmi = function () {
            if ($scope.activeMember.AgeCategory != "child") {
                $scope.calculatedBmi = (parseFloat(lastWeight) / ((parseFloat(lastLength) / 100) * (parseFloat(lastLength) / 100))).toFixed(2);
            }
        };

        var prepBmi = function () {
            if ($rootScope.activeMember.MemberLength.length > 0) {
                lastLength = $rootScope.activeMember.MemberLength[$rootScope.activeMember.MemberLength.length - 1].Value;
                calcBmi();
            } else {
                lastLength = "XXX";
                $scope.calculatedBmi = "NaN";
            }
            if ($rootScope.activeMember.MemberWeight.length > 0) {
                lastWeight = $rootScope.activeMember.MemberWeight[$rootScope.activeMember.MemberWeight.length - 1].Value;
                calcBmi();
            } else {
                lastWeight = "XX";
                $scope.calculatedBmi = "NaN";
            }
        };

        /*
        Stap4: Scope vars
        ------------------
        */

        $scope.MyPoints = $rootScope.activeMember.GamePoints;
        $scope.calculatedBmi = "NaN";

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