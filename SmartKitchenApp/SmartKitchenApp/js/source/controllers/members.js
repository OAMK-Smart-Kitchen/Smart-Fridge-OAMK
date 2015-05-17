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
            console.log("members controller started");
        };

        /*
        Stap2: Controller vars (niet in scope!)
        ------------------------------------------
        */

        var tmpHtml =
            '<div class="row">  ' +
            '<div class="col-md-12"> ' +
            '<form name="addMemberToFam" ng-submit="SendMember(addMemberToFam.$valid)" novalidate>' +
            '<!-- FIRSTNAME -->' +
            '<div class="form-group" ng-class="{ \'has-error\' : addMemberToFam.firstname.$invalid && !addMemberToFam.firstname.$pristine }">' +
            '<label>Firstname</label>' +
            '<input type="text" name="firstname" class="form-control" ng-model="newMember.Firstname" placeholder="Firstname" required autofocus>' +
            '<p ng-show="addMemberToFam.firstname.$invalid && !addMemberToFam.firstname.$pristine" class="help-block">Your firstname is required.</p>' +
            '</div>' +
            '<!-- LASTNAME -->' +
            '<div class="form-group" ng-class="{ \'has-error\' : addMemberToFam.lastname.$invalid && !addMemberToFam.lastname.$pristine }">' +
            '<label>Lastname</label>' +
            '<input type="text" name="lastname" class="form-control" ng-model="newMember.Lastname" placeholder="Lastname" required>' +
            '<p ng-show="addMemberToFam.lastname.$invalid && !addMemberToFam.lastname.$pristine" class="help-block">Your lastname is required.</p>' +
            '</div>' +
            '<!-- DATE OF BIRTH -->' +
            '<div class="form-group" ng-class="{ \'has-error\' : addMemberToFam.dateofbirth.$invalid && !addMemberToFam.dateofbirth.$pristine }">' +
            '<label>Date of Birth</label>' +
            '<input type="text" name="dateofbirth" class="form-control" ng-model="newMember.DateOfBirth" required angular-mask="00-00-0000" placeholder="dd-mm-yyyy">' +
            '<p ng-show="addMemberToFam.dateofbirth.$invalid && !addMemberToFam.dateofbirth.$pristine" class="help-block">Your Date of Birth is required.</p>' +
            '</div>' +
            '<!-- GENDER -->' +
            '<div class="form-group" ng-class="{ \'has-error\' : addMemberToFam.genderRadios.$invalid && !addMemberToFam.genderRadios.$pristine }">' +
            '<label>Select Gender</label>' +
            '<div class="radio">' +
            '<label>' +
            '<input type="radio" ng-model="newMember.Gender" name="genderRadios" value="male" required>' +
            'Male - Boy' +
            '</label>' +
            '</div>' +
            '<div class="radio">' +
            '<label>' +
            '<input type="radio" ng-model="newMember.Gender" name="genderRadios" value="female">' +
            'Female - Girl' +
            '</label>' +
            '</div>' +
            '<p ng-show="addMemberToFam.genderRadios.$invalid && !addMemberToFam.genderRadios.$pristine" class="help-block">Your gender is required.</p>' +
            '</div>' +
            '<!-- AGE CATEGORY -->' +
            '<div class="form-group" ng-class="{ \'has-error\' : addMemberToFam.agecategoryRadios.$invalid && !addMemberToFam.agecategoryRadios.$pristine }">' +
            '<label>Select Age Category</label>' +
            '<div class="radio">' +
            '<label>' +
            '<input type="radio" ng-model="newMember.AgeCategory" name="agecategoryRadios" value="adult" required>' +
            'Adult (18+)' +
            '</label>' +
            '</div>' +
            '<div class="radio">' +
            '<label>' +
            '<input type="radio" ng-model="newMember.AgeCategory" name="agecategoryRadios" value="child">' +
            'Child (1-17)' +
            '</label>' +
            '</div>' +
            '<p ng-show="addMemberToFam.agecategoryRadios.$invalid && !addMemberToFam.agecategoryRadios.$pristine" class="help-block">Your age category is required.</p>' +
            '</div>' +
            '<!-- EMAIL -->' +
            '<div class="form-group" ng-class="{ \'has-error\' : addMemberToFam.email.$invalid && !addMemberToFam.email.$pristine }">' +
            '<label>Email</label>' +
            '<input type="email" name="email" class="form-control" ng-model="newMember.Email" ng-minlength="6" placeholder="Email" no-capitalize required>' +
            '<p ng-show="addMemberToFam.email.$invalid && !addMemberToFam.email.$pristine" class="help-block">Your Email is required.</p>' +
            '</div>' +
            '<!-- SUBMIT BUTTON -->' +
            '<button type="submit" class="btn btn-primary" ng-disabled="addMemberToFam.$invalid">Register</button>' +
            '</form></div>  </div>';

        var $injector = angular.injector(['ng']);
        var $compile = $injector.get('$compile');
        var template = angular.element(tmpHtml);
        var compiledTemplate = $compile(template);
        var endHtml = compiledTemplate($scope);

        /*
        Stap3: Controller functions (niet in scope!)
        --------------------------------------------
        */

        var memberBox = function () {
            bootbox.dialog({
                title: "Add new family member to this kitchen",
                message: endHtml
            });
        };

        var playSoundWeclome = function () {
            try {
                var audio = new Audio('././sounds/welcome_dashboard.mp3');
                audio.play();
            } catch (e) {
                bootbox.alert("NO SUPPORT FOR AUDIO ON THIS BROWSER");
            }
        };

        /*
        Stap4: Scope vars
        ------------------
        */

        $scope.newMember = new app.Member();

        /* Stap5: Scope functions
        -------------------------
        */

        $scope.addMember = function () {
            console.log("Add New Member");
            memberBox();
        };

        $scope.SendMember = function (isValid) {
            try {
                if (isValid) {
                    // Send data to server
                    console.dir($scope.newMember);
                    console.log("Kitchen ID: " + app.CurrentKitchen.Id);
                    memberservice.addMember({
                        'Firstname': $scope.newMember.Firstname,
                        'Lastname': $scope.newMember.Lastname,
                        'DateOfBirth': $scope.newMember.DateOfBirth,
                        'Email': $scope.newMember.Email,
                        'Password': $scope.newMember.Password,
                        'Active': "false",
                        'Admin': "false",
                        'Gender': $scope.newMember.Gender,
                        'AgeCategory': $scope.newMember.AgeCategory,
                        'id': app.CurrentKitchen.Id
                    })
                    .$promise
                        .then(function onSuccess(data) {
                            // Data stored successfull
                            console.dir("Data Return from New Member\n" + data);
                            $scope.allMembers.push($scope.newMember);
                            bootbox.hideAll();
                        }, function onFail(data) {
                            // Something went wrong
                            console.dir("FAILED: Data Return from New Member\n" + data);
                            bootbox.hideAll();
                            bootbox.alert("<i class='fa fa-exclamation-triangle'></i> Oops, something went wrong...");
                        });
                } else {
                    bootbox.hideAll();
                    bootbox.alert("<i class='fa fa-exclamation-triangle'></i> Oops, something went wrong...");
                }
            } catch (e) {
                bootbox.hideAll();
                bootbox.alert("Something went wrong... Please try again later.");
            }
        };

        $scope.selectMember = function (num) {
            $rootScope.activeMember = $scope.allMembers[num];
            console.log("Selected APPuser ID: " + $rootScope.activeMember.Id + " \nFirst name: " + $rootScope.activeMember.Firstname);
            playSoundWeclome();
            $location.path("/dashboard");
        };


        /* Stap6: init aanroepen
        --------------------
        */
        init();

    }]);