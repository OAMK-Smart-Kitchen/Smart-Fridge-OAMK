app.controller('login', [
    '$scope',
    '$location',
    '$rootScope',
    'memberservice',
    function($scope, $location, $rootScope, memberservice) {

        /*
        Stap1: functie Init
        --------------------
        */

        // hier kan je zaken doen die ALTIJD moeten gebeuren bij het inladen van deze pagina, bijvoorbeeld: config ophalen, user checken en ophalen, een of andere call naar service met info... getNumberOfRegisterdUsers ofzo...

        var init = function() {
            console.log("login controller started");
        };

        /*
        Stap2: Controller vars (niet in scope!)
        ------------------------------------------
        */


        /*
        Stap3: Controller functions (niet in scope!)
        --------------------------------------------
        */
        var resetRegisterForm = function() {
            $scope.reg_section_one = true;
            $scope.reg_section_two = false;
            $scope.reg_section_three = false;
            $scope.Member.Password = "";
            $scope.TempPassword = "";
            $scope.ConfirmTempPassword = "";
            $scope.Member.Email = "";
            $scope.Member.Firstname = "";
            $scope.Member.Lastname = "";
            $scope.Member.DateOfBirth = null;
            $scope.Kitchen.Name = "";
        };

        var processData = function (data) {
            app.CurrentKitchen.Id = data.Id;
            app.CurrentKitchen.Name = data.Name;
            app.CurrentKitchen.TemperatureFridge = data.TemperatureFridge;
            for (var i = 0; i < data.Members.length; i++) {
                var selectedMember = data.Members[i];
                $scope.allMembers.push(selectedMember);
                if (selectedMember.Admin == "true") {
                    // The currentMember is the admin of the kitchen and used for authentication on the server.
                    app.CurrentMember = selectedMember;
                    // Active Member is the member for get en set data in the app
                    $rootScope.activeMember = selectedMember;
                }
            }
        };

        var loginKitchen = function() {
            try {
                $scope.loginStatus = 1; //LOADING
                $scope.Member.Password = String(app.CryptoJS($scope.Member.Email + $scope.TempPassword));
                memberservice.memberLogin({ 'Email': $scope.Member.Email, 'Password': $scope.Member.Password }) // + '' typecast to string
                    .$promise
                    .then(function onSuccess(data) {
                        processData(data);
                        //EMPTY form
                        resetRegisterForm();
                        $scope.loginStatus = 3; //SUCCESS
                        //Navigate to Members page
                        $location.path("/members");
                    }, function onFail(data) {
                        $scope.loginStatus = 2; // Error
                        $scope.errorMessage = data.message;
                    });
            } catch (e) {
                console.log("An login Error occurred: " + e.message);
            }
        };

        var registerKitchen = function() {
            try {
                $scope.registerStatus = 1;
                $scope.Member.Password = String(app.CryptoJS($scope.Member.Email + $scope.TempPassword));
                memberservice.memberRegister({
                        'Firstname': $scope.Member.Firstname,
                        'Lastname': $scope.Member.Lastname,
                        'DateOfBirth': $scope.Member.DateOfBirth,
                        'Email': $scope.Member.Email,
                        'Password': $scope.Member.Password,
                        'Active': "true",
                        'Admin': "true",
                        'KitchenName': $scope.Kitchen.Name
                    }) // + '' typecast to string
                    .$promise
                    .then(function onSuccess(data) {
                        processData(data);
                        $scope.registerStatus = 3; //Success
                        //Navigate to Members page
                        $location.path("/members");
                    }, function onFail(data) {
                        $scope.registerStatus = 2; //error
                    });

            } catch (e) {
                console.log("An register Error occurred: " + e.message);
            }
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
        $scope.errorMessage = "Unknown Error";

        $scope.reg_section_one = true;
        $scope.reg_section_two = false;
        $scope.reg_section_three = false;

        $scope.Member = app.Member;
        $scope.Kitchen = app.Kitchen;

        $rootScope.activeMember = null;

        /* Stap5: Scope functions
        -------------------------
        */
        // Toggle Login-Register tabs
        $scope.switchTo = function(name) {
            if ((name == "login") && ($scope.showlogin == false) && ($scope.showregister == true)) {
                resetRegisterForm();
                $scope.showlogin = true;
                $scope.showregister = false;
                $scope.loginStatus = 0;
                $scope.registerStatus = 0;
            } else if ((name == "register") && ($scope.showlogin == true) && ($scope.showregister == false)) {
                resetRegisterForm();
                $scope.showlogin = false;
                $scope.showregister = true;
                $scope.loginStatus = 0;
                $scope.registerStatus = 0;
            }
        };

        // Register Member with kitchen
        $scope.kitchenDone = function(isValid) {
            if (isValid) {
                $scope.reg_section_one = false;
                $scope.reg_section_two = true;
                $scope.reg_section_three = false;
                console.log("Kitchen data success");
            }
        };

        $scope.adminDone = function(isValid) {
            if (isValid) {
                registerKitchen();
                $scope.reg_section_one = false;
                $scope.reg_section_two = false;
                $scope.reg_section_three = true;
            }
        };


        //NAVIGATION
        $scope.goToDashboard = function(isValid) {
            if (isValid) {
                loginKitchen();
            }
        };

        /* Stap6: init aanroepen
        --------------------
        */
        init();

    }
]);