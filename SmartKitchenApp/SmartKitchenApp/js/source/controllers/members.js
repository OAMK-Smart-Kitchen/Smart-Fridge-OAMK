app.controller('members', [
    '$scope',
    '$location',
    '$rootScope',
    'memberservice',
    function ($scope, $location, $rootScope, memberservice) {

        /*
        Stap1: functie Init
        --------------------
        */

        // hier kan je zaken doen die ALTIJD moeten gebeuren bij het inladen van deze pagina, bijvoorbeeld: config ophalen, user checken en ophalen, een of andere call naar service met info... getNumberOfRegisterdUsers ofzo...

        var init = function () {
            console.log('members controller started');
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

        

        /* Stap5: Scope functions
        -------------------------
        */
        
        $scope.addMember = function () {

        };

        $scope.selectMember = function (num) {
            $scope.activeMember = $scope.allMembers[num];
            console.log("Selected user ID: " + $scope.allMembers[num].Id + " \nFirst name: " + $scope.allMembers[num].Firstname);
            console.log("Selected APPuser ID: " + $scope.activeMember.Id + " \nFirst name: " + $scope.activeMember.Firstname);
        };

       
        /* Stap6: init aanroepen
        --------------------
        */
        init();

    }]);