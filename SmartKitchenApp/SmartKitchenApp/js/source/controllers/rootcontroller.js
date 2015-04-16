app.controller('rootcontroller', [
    '$scope',
    '$rootScope',
    '$location',
    function ($rootScope, $scope, $location) {

        /*
        Stap1: functie Init
        --------------------
        */

        // hier kan je zaken doen die ALTIJD moeten gebeuren bij het inladen van deze pagina, bijvoorbeeld: config ophalen, user checken en ophalen, een of andere call naar service met info... getNumberOfRegisterdUsers ofzo...

        var init = function () {
            console.log("root controller started");
        };

        /*
        Stap2: Controller vars (niet in scope!)
        ------------------------------------------
        */


        /*
        Stap3: Controller functions (niet in scope!)
        --------------------------------------------
        */

        var goToLogin = function () {
            console.log("Navigate to Login");
            $location.path("/login");
        };

        var goToMembers = function () {
            console.log("Navigate to user panel");
            $location.path("/members");
        };

        /*
        Stap4: Scope vars
        ------------------
        */

        $rootScope.getCopyright = "\u00A9 " + new Date().getFullYear() + " Smart Kitchen Project";
        $scope.currentPage;
        $scope.allMembers = new Array();

        /* Stap5: Scope functions
        -------------------------
        */

        $scope.$on('$routeChangeSuccess', function() { 
            $scope.currentPage = $location.path();
            //console.log("DEBUG_LOG: " + $scope.currentPage);
            console.log("The activeMember is:");
            console.dir($rootScope.activeMember);
        });

        $rootScope.goToGetStarted = function () {
            console.log("Navigate to GetStarted");
            $location.path("/get-started");
        };

        $rootScope.goToAbout = function () {
            console.log("Navigate to About");
            $location.path("/about");
        };

        $rootScope.enterKitchen = function() {
            if ($rootScope.activeMember == null) {
                goToLogin();
            } else {
                goToMembers();
            }
        };

        $rootScope.goToRoot = function () {
            console.log("Navigate to Root");
            $location.path("/");
        };

        /* Stap6: init aanroepen
        --------------------
        */
        init();
    }
]);