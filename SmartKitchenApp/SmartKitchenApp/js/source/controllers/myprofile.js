app.controller('myprofile', [
    '$scope',
    '$rootScope',
    'memberservice',
    function ($scope, $rootScope, memberservice) {

        /*
        Stap1: functie Init
        --------------------
        */

        var init = function () {
            console.log("myprofile controller started");
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

        $scope.editedMember = new app.Member(); //$rootScope.activeMember
        $scope.editedMember = $rootScope.activeMember;

        /* Stap5: Scope functions
        -------------------------
        */

        $scope.toggleGameActivated = function (isState) {
            if (isState == "true") {
                $scope.editedMember.GameActivated = "false";
            } else if (isState == "false") {
                $scope.editedMember.GameActivated = "true";
            }
        };

        $scope.editProfile = function (isValid) {
            if (isValid) {
                console.log("New credentials:");
                console.dir($scope.editedMember);
                // Save the new member information and push to server
                $rootScope.activeMember = $scope.editedMember;
                memberservice.updateProfile({
                    'id': $scope.editedMember.Id,
                    'Firstname': $scope.editedMember.Firstname,
                    'Lastname': $scope.editedMember.Lastname,
                    'DateOfBirth': $scope.editedMember.DateOfBirth,
                    'Email': $scope.editedMember.Email,
                    'Active': $scope.editedMember.Active,
                    'DefaultColor': $scope.editedMember.DefaultColor,
                    'GameActivated': $scope.editedMember.GameActivated
            })
                 .$promise
                        .then(function onSuccess(data) {
                            // Data stored successfull
                            // Update list of all members
                            //$scope.allMembers.push($scope.newMember);
                            bootbox.hideAll();
                            bootbox.dialog({
                                title: "<h1 class='text-center'>Hooray!!</h1>",
                                message: "<h2 class='text-center'><i class='fa fa-thumbs-o-up'></i>&nbsp; Your profile has been updated successfully.</h2>",
                                buttons: {
                                    success: {
                                        label: "Thanks!",
                                        className: "btn-success"
                                    }
                                }
                            });
                        }, function onFail(data) {
                            // Something went wrong
                            console.log("FAILED: Data Return from Edit Members Profile");
                            console.dir(data);
                    });
            }
        };
       

        /* Stap6: init aanroepen
        --------------------
        */
        init();

    }]);