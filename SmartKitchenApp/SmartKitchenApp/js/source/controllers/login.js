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
        var resetRegisterForm = function () {
            $scope.reg_section_one = true;
            $scope.reg_section_two = false;
            $scope.reg_section_three = false;
            $scope.Member.Password = null;
            $scope.Member.Email = null;
            $scope.Member.Firstname = null;
            $scope.Member.Lastname = null;
            $scope.Member.DateOfBirth = null;
            $scope.Kitchen.Name = null;
        };

        /*
        Stap4: Scope vars
        ------------------
        */
        // Status options
        // 0 : Nothing happend everything is fine
        // 1 : Processing 
        // 2 : Failed-Error
        // 3 : Success

        $scope.loginStatus = 0;

        $scope.registerStatus = 0;

        $scope.showlogin = true;
        $scope.showregister = false;

        $scope.reg_section_one = true;
        $scope.reg_section_two = false;
        $scope.reg_section_three = false;


        /* Stap5: Scope functions
        -------------------------
        */
        // Toggle Login-Register tabs
        $scope.switchTo = function (name) {
            if (name == 'login') {
                resetRegisterForm();

                $scope.showlogin = true;
                $scope.showregister = false;
            }
            else
                if (name == 'register') {
                    $scope.showlogin = false;
                    $scope.showregister = true;
                }
        };

        // Register Member with kitchen
        $scope.kitchenDone = function (isValid) {
            if (isValid) {
                $scope.reg_section_one = false;
                $scope.reg_section_two = true;
                $scope.reg_section_three = false;
                console.log("Kitchen data success");
            }
        };

        $scope.adminDone = function (isValid) {
            if (isValid) {
                $scope.reg_section_one = false;
                $scope.reg_section_two = false;
                $scope.reg_section_three = true;
                console.log("Member data register success");
            }
        };


        //NAVIGATION
        $scope.goToDashboard = function (isValid) {
            if (isValid) {
                //$location.path("/dashboard/:kitchen.id/member");
                $location.path("/members");
                console.log("Navigate to Member Dasboard");
                console.log("Kitchen ID: " + kitchen.id);
            }
        };

        /* Stap6: init aanroepen
        --------------------
        */
        init();

    }]);