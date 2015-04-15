app.service('memberservice', [
    '$resource',
    function ($resource) {
        var MemberService = $resource(app.serviceUrl, null, {
            Login: {
                url: app.serviceUrl + 'Kitchen/Login',
                method: "POST",
                headers: {
                    'Content-Type': 'application/json'
                },
                params: {
                    Email: '@email',
                    Password: '@password',
                }
            },
            Register: {
                url: app.serviceUrl + 'Kitchen/Register',
                method: "POST",
                headers: {
                    'Content-Type': 'application/json'
                },
                params: {
                    KitchenName: '@kitchenname',
                    Firstname: '@firstname',
                    Lastname: '@lastname',
                    DateOfBirth: '@dateofbirth',
                    Email: '@email',
                    Password: '@password',
                    Active: '@active',
                    Admin: '@admin'
                }
            },
            AddMember: {
                url: app.serviceUrl + 'Members/Register',
                method: "POST",
                headers: {
                    'Content-Type': 'application/json'
                },
                params: {
                    data: '@member'
                }
            },
            UpdateProfile: {
                url: app.serviceUrl + 'Kitchen/Update',
                method: 'PUT',
                headers: {
                    'Content-Type': 'application/json'
                },
                params: {
                    data: '@member'
                }
            },
            ForgotPassword: {
                url: app.serviceUrl + 'Members/ForgotPassword',
                method: "POST",
                headers: {
                    'Content-Type': 'application/json'
                },
                params: {
                    data: '@member'
                }
            }

        }
        );

        var API = {
            memberLogin: MemberService.Login,
            memberRegister: MemberService.Register,
            memberAdd: MemberService.AddMember,
            updateProfile: MemberService.UpdateProfile,
            memberForgotPassword: MemberService.ForgotPassword
        };

        return API;
    }
]);